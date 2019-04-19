#ifndef __APPLICATION_CONFIGURATION_H
#define __APPLICATION_CONFIGURATION_H

#include <string>
#include <vector>

class ApplicationConfiguration
{
	bool write_video_flag = false;
	bool run_test_flag = false;
	std::vector<std::string> option_models;

public:
	ApplicationConfiguration();

	bool get_write_video_flag() const;
	bool get_run_test_flag() const;

	int parse_arguments(int argc, char* argv[]);

private:
	// Disable copy constructor
	ApplicationConfiguration(const ApplicationConfiguration&); // no implementation 
	ApplicationConfiguration& operator=(const ApplicationConfiguration&); // no implementation 
};

#endif /* __APPLICATION_CONFIGURATION_H */
