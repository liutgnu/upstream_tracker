#include <iostream>
#include <string>
#include <cstdio>
#include "tracker.h"

std::string upstream_project_urls[][3] = {
	{"crash upstream", "crash-", "https://github.com/crash-utility/crash"},
	{"crash fedora", "", "https://src.fedoraproject.org/rpms/crash/raw/rawhide/f/crash.spec"},
	{"crash rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/crash/plain/crash.spec?h=rhel-9-main"},
	{"kexec-tools upstream", "v200[6-8][0-9]{4}", "https://git.kernel.org/pub/scm/utils/kernel/kexec/kexec-tools.git"},
	{"kexec-tools fedora", "", "https://src.fedoraproject.org/rpms/kexec-tools/raw/rawhide/f/kexec-tools.spec"},
	{"kexec-tools rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/kexec-tools/plain/kexec-tools.spec?h=rhel-9-main"},
	{"makedumpfile upstream", "pubkey|start|Released|DEVEL", "https://github.com/makedumpfile/makedumpfile.git"},
	{"irqbalance upstream", "", "https://github.com/Irqbalance/irqbalance.git"},
	{"irqbalance fedora", "", "https://src.fedoraproject.org/rpms/irqbalance/raw/rawhide/f/irqbalance.spec"},
	{"irqbalance rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/irqbalance/plain/irqbalance.spec?h=rhel-9-main"},
	{"lshw upstream", "[AT]\\.[0-9]{2}\\.[0-9]{2}", "https://github.com/lyonel/lshw.git"},
	{"lshw fedora", "", "https://src.fedoraproject.org/rpms/lshw/raw/rawhide/f/lshw.spec"},
	{"lshw rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/lshw/plain/lshw.spec?h=rhel-9-main"},
	{"dracut upstream", "RHEL|0\\.[1-9]", "https://github.com/dracutdevs/dracut.git"},
	{"dracut fedora", "", "https://src.fedoraproject.org/rpms/dracut/raw/rawhide/f/dracut.spec"},
	{"dracut rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/dracut/plain/dracut.spec?h=rhel-9-main"},
	{"memstrack upstream", "", "https://github.com/ryncsn/memstrack.git"},
	{"memstrack fedora", "", "https://src.fedoraproject.org/rpms/memstrack/raw/rawhide/f/memstrack.spec"},
	{"memstrack rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/memstrack/plain/memstrack.spec?h=rhel-9-main"},
	{"crash-gcore-command upstream", "", "https://github.com/fujitsu/crash-gcore.git"},
	{"crash-gcore-command fedora", "", "https://src.fedoraproject.org/rpms/crash-gcore-command/raw/rawhide/f/crash-gcore-command.spec"},
	{"crash-gcore-command rhel", "", "http://pkgs.devel.redhat.com/cgit/rpms/crash-gcore-command/plain/crash-gcore-command.spec?h=rhel-9-main"},
};

int main(int argc, char **argv)
{
	printf("%#51s%#25s%#25s","Upstream", "Fedora rawhide", "Rhel 9-main");
	for (int i = 0; 
	     i < sizeof(upstream_project_urls)/sizeof(upstream_project_urls[0]); 
	     i += 1) {
		Tracker t(upstream_project_urls[i][0], upstream_project_urls[i][2], upstream_project_urls[i][1]);
		Tracker *p = t.init();
		p->query();
		p->display();
		delete p;
	}
	std::cout << endl;
	return 0;
}   