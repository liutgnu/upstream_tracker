#include <iostream>
#include <string>
#include "tracker.h"

std::string upstream_project_urls[][3] = {
	{"crash upstream", "crash-", "https://github.com/crash-utility/crash"},
	{"crash fedora", "", "https://src.fedoraproject.org/rpms/crash/raw/rawhide/f/crash.spec"},
	{"kexec-tools upstream", "v200[6-8][0-9]{4}", "https://git.kernel.org/pub/scm/utils/kernel/kexec/kexec-tools.git"},
	{"kexec-tools fedora", "", "https://src.fedoraproject.org/rpms/kexec-tools/raw/rawhide/f/kexec-tools.spec"},
	{"irqbalance upstream", "", "https://github.com/Irqbalance/irqbalance.git"},
	{"irqbalance fedora", "", "https://src.fedoraproject.org/rpms/irqbalance/raw/rawhide/f/irqbalance.spec"},
	{"lshw upstream", "[AT]\\.[0-9]{2}\\.[0-9]{2}", "https://github.com/lyonel/lshw.git"},
	{"lshw fedora", "", "https://src.fedoraproject.org/rpms/lshw/raw/rawhide/f/lshw.spec"},
	{"dracut upstream", "RHEL|0\\.[1-9]", "https://github.com/dracutdevs/dracut.git"},
	{"dracut fedora", "", "https://src.fedoraproject.org/rpms/dracut/raw/rawhide/f/dracut.spec"},
	{"memstrack upstream", "", "https://github.com/ryncsn/memstrack.git"},
	{"memstrack fedora", "", "https://src.fedoraproject.org/rpms/memstrack/raw/rawhide/f/memstrack.spec"},
	{"crash-gcore-command upstream", "", "https://github.com/fujitsu/crash-gcore.git"},
	{"crash-gcore-command fedora", "", "https://src.fedoraproject.org/rpms/crash-gcore-command/raw/rawhide/f/crash-gcore-command.spec"},
};

int main(int argc, char **argv)
{
	for (int i = 0; 
	     i < sizeof(upstream_project_urls)/sizeof(upstream_project_urls[0]); 
	     i += 1) {
		std::cout << "===" + upstream_project_urls[i][0] + "===" << std::endl;
		Tracker t(upstream_project_urls[i][0], upstream_project_urls[i][2], upstream_project_urls[i][1]);
		std::cout << t.init()->query() << std::endl;
	}
	return 0;
}