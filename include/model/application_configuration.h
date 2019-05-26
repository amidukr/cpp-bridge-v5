#ifndef __APPLICATION_CONFIGURATION_H
#define __APPLICATION_CONFIGURATION_H

#include <string>
#include <vector>
#include <memory>

class SimulationOption;

class ApplicationConfiguration
{
	bool write_video_flag = false;
	bool run_test_flag = false;
	std::vector<std::shared_ptr<SimulationOption>> simulation_options;
	bool headless_mode_flag = false;

public:
	ApplicationConfiguration();

	void add_simulation_option(std::shared_ptr<SimulationOption> simulation_option);
	const std::vector<std::shared_ptr<SimulationOption>>& get_simulation_options() const;

	bool get_write_video_flag() const;
	void set_write_video_flag(bool write_video_flag);

	bool get_run_test_flag() const;
	void set_run_test_flag(bool run_test_flag);

	void set_headless_mode_flag(bool headless_mode);
	bool get_headless_mode_flag();

private:
	// Disable copy constructor
	ApplicationConfiguration(const ApplicationConfiguration&); // no implementation 
	ApplicationConfiguration& operator=(const ApplicationConfiguration&); // no implementation 
};

#endif /* __APPLICATION_CONFIGURATION_H */
