#include <iostream>
#include <string>
#include <cstdio>
#include <future>
#include <thread>
#include <tuple>
#include "tracker.h"

std::string upstream_project_urls[][3] = {
	{"crash upstream", "crash-", "https://github.com/crash-utility/crash"},
	{"crash fedora", "", "https://src.fedoraproject.org/rpms/crash/raw/rawhide/f/crash.spec"},
	{"crash rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash/plain/crash.spec?h=rhel-9-main"},
	{"crash rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash/plain/crash.spec?h=rhel-8.8.0"},
	{"kexec-tools upstream", "v200[6-8][0-9]{4}", "https://git.kernel.org/pub/scm/utils/kernel/kexec/kexec-tools.git"},
	{"kexec-tools fedora", "", "https://src.fedoraproject.org/rpms/kexec-tools/raw/rawhide/f/kexec-tools.spec"},
	{"kexec-tools rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/kexec-tools/plain/kexec-tools.spec?h=rhel-9-main"},
	{"kexec-tools rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/kexec-tools/plain/kexec-tools.spec?h=rhel-8.8.0"},
	{"makedumpfile upstream", "pubkey|start|Released|DEVEL", "https://github.com/makedumpfile/makedumpfile.git"},
	{"irqbalance upstream", "", "https://github.com/Irqbalance/irqbalance.git"},
	{"irqbalance fedora", "", "https://src.fedoraproject.org/rpms/irqbalance/raw/rawhide/f/irqbalance.spec"},
	{"irqbalance rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/irqbalance/plain/irqbalance.spec?h=rhel-9-main"},
	{"irqbalance rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/irqbalance/plain/irqbalance.spec?h=rhel-8.8.0"},
	{"lshw upstream", "[AT]\\.[0-9]{2}\\.[0-9]{2}", "https://github.com/lyonel/lshw.git"},
	{"lshw fedora", "", "https://src.fedoraproject.org/rpms/lshw/raw/rawhide/f/lshw.spec"},
	{"lshw rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/lshw/plain/lshw.spec?h=rhel-9-main"},
	{"lshw rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/lshw/plain/lshw.spec?h=rhel-8.8.0"},
	{"dracut upstream", "RHEL|0\\.[1-9]", "https://github.com/dracutdevs/dracut.git"},
	{"dracut fedora", "", "https://src.fedoraproject.org/rpms/dracut/raw/rawhide/f/dracut.spec"},
	{"dracut rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/dracut/plain/dracut.spec?h=rhel-9-main"},
	{"dracut rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/dracut/plain/dracut.spec?h=rhel-8.8.0"},
	{"memstrack upstream", "", "https://github.com/ryncsn/memstrack.git"},
	{"memstrack fedora", "", "https://src.fedoraproject.org/rpms/memstrack/raw/rawhide/f/memstrack.spec"},
	{"memstrack rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/memstrack/plain/memstrack.spec?h=rhel-9-main"},
	{"memstrack rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/memstrack/plain/memstrack.spec?h=rhel-8.8.0"},
	{"crash-gcore-command upstream", "", "https://github.com/fujitsu/crash-gcore.git"},
	{"crash-gcore-command fedora", "", "https://src.fedoraproject.org/rpms/crash-gcore-command/raw/rawhide/f/crash-gcore-command.spec"},
	{"crash-gcore-command rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash-gcore-command/plain/crash-gcore-command.spec?h=rhel-9-main"},
	{"crash-gcore-command rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash-gcore-command/plain/crash-gcore-command.spec?h=rhel-8.8.0"},
	{"dmidecode upstream", "", "https://github.com/mirror/dmidecode.git"},
	{"dmidecode fedora", "", "https://src.fedoraproject.org/rpms/dmidecode/raw/rawhide/f/dmidecode.spec"},
	{"dmidecode rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/dmidecode/plain/dmidecode.spec?h=rhel-9-main"},
	{"dmidecode rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/dmidecode/plain/dmidecode.spec?h=rhel-8.8.0"},
	{"py-dmidecode upstream", "", "https://github.com/nima/python-dmidecode.git"},
	{"py-dmidecode fedora", "", "https://src.fedoraproject.org/rpms/python-dmidecode/raw/rawhide/f/python-dmidecode.spec"},
	{"py-dmidecode rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/python-dmidecode/plain/python-dmidecode.spec?h=rhel-9-main"},
	{"py-dmidecode rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/python-dmidecode/plain/python-dmidecode.spec?h=rhel-8.8.0"},
	//{"libtopology"},
	{"numactl upstream", "", "https://github.com/numactl/numactl.git"},
	{"numactl fedora", "", "https://src.fedoraproject.org/rpms/numactl/raw/rawhide/f/numactl.spec"},
	{"numactl rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/numactl/plain/numactl.spec?h=rhel-9-main"},
	{"numactl rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/numactl/plain/numactl.spec?h=rhel-8.8.0"},
	{"numatop upstream", "", "https://github.com/intel/numatop.git"},
	{"numatop fedora", "", "https://src.fedoraproject.org/rpms/numatop/raw/rawhide/f/numatop.spec"},
	{"numatop rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/numatop/plain/numatop.spec?h=rhel-9-main"},
	{"numatop rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/numatop/plain/numatop.spec?h=rhel-8.8.0"},
	{"snappy upstream", "", "https://github.com/google/snappy.git"},
	{"snappy fedora", "", "https://src.fedoraproject.org/rpms/snappy/raw/rawhide/f/snappy.spec"},
	{"snappy rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/snappy/plain/snappy.spec?h=rhel-9-main"},
	{"snappy rhel8", "", "https://pkgs.devel.redhat.com/cgit/rpms/snappy/plain/snappy.spec?h=rhel-8.8.0"},
};

int main(int argc, char **argv)
{
	printf("%#51s%#25s%#25s%#25s","Upstream", "Fedora rawhide", "Rhel 9-main", "Rhel 8");
	std::vector<std::tuple<Tracker *, std::future<void>>> tracker_future_list;

	for (int i = 0; 
	     i < sizeof(upstream_project_urls)/sizeof(upstream_project_urls[0]); 
	     i += 1) {
		Tracker t(upstream_project_urls[i][0], upstream_project_urls[i][2], upstream_project_urls[i][1]);
		Tracker *p = t.init();
		tracker_future_list.push_back(make_tuple(p, std::async(std::launch::async, &Tracker::query, p)));
	}
	for (auto&& it:tracker_future_list) {
		get<1>(it).get();
		get<0>(it)->display();
		delete(get<0>(it));
	}
	std::cout << endl;
	return 0;
}   
