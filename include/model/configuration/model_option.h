#ifndef __MODEL_OPTION_H
#define __MODEL_OPTION_H

#include <string>
#include <vector>

class ModelOption
{
	std::vector<std::string> controllers;
	std::vector<std::string> maps;
	std::vector<std::string> options;

public:
	ModelOption();

	const std::vector<std::string>& get_controllers() const;
	const std::vector<std::string>& get_maps() const;
	const std::vector<std::string>& get_options() const;
	
	void add_controller(std::string controller);
	void add_map(std::string map);
	void add_option(std::string option);

private:
	// Disable copy constructor
	ModelOption(const ModelOption&); // no implementation 
	ModelOption& operator=(const ModelOption&); // no implementation 
};

#endif /* __MODEL_OPTION_H */
