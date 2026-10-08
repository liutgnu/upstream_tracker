#include <iostream>
#include <string>
#include <cstdio>
#include <future>
#include <thread>
#include <tuple>
#include "tracker.h"

std::string upstream_project_urls[][3] = {
	{"kernel upstream", "", "https://github.com/torvalds/linux"},
	{"kernel fedora", "", "https://src.fedoraproject.org/rpms/kernel/raw/rawhide/f/kernel.spec"},
	{"kernel rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/kernel/plain/kernel.spec?h=rhel-9-main"},
	{"kernel rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/kernel/plain/kernel.spec?h=rhel-10-main"},
	{"crash upstream", "crash-", "https://github.com/crash-utility/crash"},
	{"crash fedora", "", "https://src.fedoraproject.org/rpms/crash/raw/rawhide/f/crash.spec"},
	{"crash rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash/plain/crash.spec?h=rhel-9-main"},
	{"crash rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash/plain/crash.spec?h=rhel-10-main"},
	{"kexec-tools upstream", "v200[6-8][0-9]{4}", "https://git.kernel.org/pub/scm/utils/kernel/kexec/kexec-tools.git"},
	{"kexec-tools fedora", "", "https://src.fedoraproject.org/rpms/kexec-tools/raw/rawhide/f/kexec-tools.spec"},
	{"kexec-tools rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/kexec-tools/plain/kexec-tools.spec?h=rhel-9-main"},
	{"kexec-tools rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/kexec-tools/plain/kexec-tools.spec?h=rhel-10-main"},
	{"kdump-utils upstream", "", "https://github.com/rhkdump/kdump-utils.git"},
	{"kdump-utils fedora", "", "https://src.fedoraproject.org/rpms/kdump-utils/raw/rawhide/f/kdump-utils.spec"},
	{"kdump-utils rhel9", "", ""},
	{"kdump-utils rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/kdump-utils/plain/kdump-utils.spec?h=rhel-10-main"},
	{"makedumpfile upstream", "pubkey|start|Released|DEVEL", "https://github.com/makedumpfile/makedumpfile.git"},
	{"makedumpfile fedora", "", "https://src.fedoraproject.org/rpms/makedumpfile/raw/rawhide/f/makedumpfile.spec"},
	{"makedumpfile rhel9", "", ""},
	{"makedumpfile rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/makedumpfile/plain/makedumpfile.spec?h=rhel-10-main"},
	{"memstrack upstream", "", "https://github.com/ryncsn/memstrack.git"},
	{"memstrack fedora", "", "https://src.fedoraproject.org/rpms/memstrack/raw/rawhide/f/memstrack.spec"},
	{"memstrack rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/memstrack/plain/memstrack.spec?h=rhel-9-main"},
	{"memstrack rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/memstrack/plain/memstrack.spec?h=rhel-10-main"},
	{"crash-gcore-command upstream", "", "https://github.com/fujitsu/crash-gcore.git"},
	{"crash-gcore-command fedora", "", "https://src.fedoraproject.org/rpms/crash-gcore-command/raw/rawhide/f/crash-gcore-command.spec"},
	{"crash-gcore-command rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash-gcore-command/plain/crash-gcore-command.spec?h=rhel-9-main"},
	{"crash-gcore-command rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash-gcore-command/plain/crash-gcore-command.spec?h=rhel-10-main"},
	{"crash-trace-command upstream", "", "https://github.com/fujitsu/crash-trace.git"},
	{"crash-trace-command fedora", "", "https://src.fedoraproject.org/rpms/crash-trace-command/raw/rawhide/f/crash-trace-command.spec"},
	{"crash-trace-command rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash-trace-command/plain/crash-trace-command.spec?h=rhel-9-main"},
	{"crash-trace-command rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/crash-trace-command/plain/crash-trace-command.spec?h=rhel-10-main"},
	{"drgn upstream", "vmtest-", "https://github.com/osandov/drgn"},
	{"drgn fedora", "", "https://src.fedoraproject.org/rpms/python-drgn/raw/rawhide/f/python-drgn.spec"},
	{"drgn rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/python-drgn/plain/python-drgn.spec?h=rhel-9-main"},
	{"drgn rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/python-drgn/plain/python-drgn.spec?h=rhel-10-main"},
	{"libkdumpfile upstream", "", "https://codeberg.org/ptesarik/libkdumpfile.git"},
	{"libkdumpfile fedora", "", "https://src.fedoraproject.org/rpms/libkdumpfile/raw/rawhide/f/libkdumpfile.spec"},
	{"libkdumpfile rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/libkdumpfile/plain/libkdumpfile.spec?h=rhel-9-main"},
	{"libkdumpfile rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/libkdumpfile/plain/libkdumpfile.spec?h=rhel-10-main"},
	{"kdump-anaconda-addon upstream", "", "https://github.com/rhinstaller/kdump-anaconda-addon.git"},
	{"kdump-anaconda-addon fedora", "", "https://src.fedoraproject.org/rpms/kdump-anaconda-addon/raw/rawhide/f/kdump-anaconda-addon.spec"},
	{"kdump-anaconda-addon rhel9", "", "https://pkgs.devel.redhat.com/cgit/rpms/kdump-anaconda-addon/plain/kdump-anaconda-addon.spec?h=rhel-9-main"},
	{"kdump-anaconda-addon rhel10", "", "https://pkgs.devel.redhat.com/cgit/rpms/kdump-anaconda-addon/plain/kdump-anaconda-addon.spec?h=rhel-10-main"},
};

int main(int argc, char **argv)
{
	printf("%#52s%#26s%#26s%#26s","Upstream", "Fedora rawhide", "Rhel 9", "Rhel 10");
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
