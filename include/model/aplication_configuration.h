#ifndef __APPLICATION_CONFIGURATION_H
#define __APPLICATION_CONFIGURATION_H

#include <string>
#include <vector>
#include <memory>

class ModelOption;

class ApplicationConfiguration
{
	bool write_video_flag = false;
	bool run_test_flag = false;
	std::vector<std::shared_ptr<ModelOption>> model_options;

public:
	ApplicationConfiguration();

	void add_model_option(std::shared_ptr<ModelOption> model_option);
	const std::vector<std::shared_ptr<ModelOption>>& get_model_options() const;

	bool get_write_video_flag() const;
	void set_write_video_flag(bool write_video_flag);

	bool get_run_test_flag() const;
	void set_run_test_flag(bool run_test_flag);

private:
	// Disable copy constructor
	ApplicationConfiguration(const ApplicationConfiguration&); // no implementation 
	ApplicationConfiguration& operator=(const ApplicationConfiguration&); // no implementation 
};

#endif /* __APPLICATION_CONFIGURATION_H */
