FROM fedora:latest AS builder

RUN dnf -y install gcc-c++ make \
    && dnf clean all

WORKDIR /src
COPY . .

RUN make

# Runtime stage
FROM fedora:latest

RUN dnf -y install libstdc++ rpm-build git curl \
    && dnf clean all \
    && useradd --system --uid 10001 tracker

WORKDIR /app
COPY --from=builder /src/main /app/upstream_tracker

USER 10001:10001

ENTRYPOINT ["/app/upstream_tracker"]