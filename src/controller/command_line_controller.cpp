#include "controller/command_line_controller.h"

#include "model/aplication_configuration.h"
#include "model/configuration/model_option.h"

#include <iostream>
#include <args.hxx>


CommandLineController::CommandLineController(std::shared_ptr<ApplicationConfiguration> application_configuration)
{
	this->application_configuration = application_configuration;
}

void print_simulation_help() {
	std::cout << "Simulation model help" << std::endl;
	std::cout << std::endl;
	std::cout << "  cpp-bridge-v5.exe [models...] {OPTIONS}" << std::endl;
	std::cout << std::endl;
	std::cout << "  Format for 'models' option: {list-of-contollers}:{list-of-maps}:{list-of-options}" << std::endl;
	std::cout << "     Format for 'list-of-contollers'   - controller1[,controller1,..] | *" << std::endl;
	std::cout << "     Format for 'list-of-maps'         - map1[,map2,..] | *" << std::endl;
	std::cout << "     Format for 'list-of-options'      - option1[,option2,..] | *" << std::endl;
	std::cout << "  Example: *:rope,pandulum:100x" << std::endl;
}

int split_comma_string(const std::string& string, std::vector<std::string>& result) {
	std::stringstream stream(string);

	do {
		std::string token;

		std::getline(stream, token, ',');

		if (token == "") return 1;

		result.push_back(token);

	} while (!stream.eof());

	if (result.size() > 1) {
		for (const auto value : result) {
			if (value == "*") return 1;
		}
	}
	
	return 0;
}

int parse_controllers(std::shared_ptr<ModelOption> model_option, const std::string& string_value) {
	std::vector<std::string> vector;
	if (split_comma_string(string_value, vector)) return 1;

	for (const auto value : vector) {
		model_option->add_controller(value);
	}

	return 0;
}

int parse_maps(std::shared_ptr<ModelOption> model_option, const std::string string_value) {
	std::vector<std::string> vector;
	if (split_comma_string(string_value, vector)) return 1;

	for (const auto value : vector) {
		model_option->add_map(value);
	}

	return 0;
}

int parse_options(std::shared_ptr<ModelOption> model_option, const std::string string_value) {
	std::vector<std::string> vector;
	if (split_comma_string(string_value, vector)) return 1;

	for (const auto value : vector) {
		model_option->add_option(value);
	}

	return 0;
}

int CommandLineController::parse_models(const std::vector<std::string>& models) {
	
	for (const auto model : models) {

		std::stringstream model_stream(model);

		std::string controller;
		std::string map;
		std::string model;

		if (model_stream.eof()) return 1;
		std::getline(model_stream, controller, ':');

		if (model_stream.eof()) return 1;
		std::getline(model_stream, map, ':');

		if (model_stream.eof()) return 1;
		std::getline(model_stream, model);

		std::shared_ptr<ModelOption> model_option(new ModelOption());

		if (parse_controllers(model_option, controller)) return 1;
		if (parse_maps(model_option, map)) return 1;
		if (parse_options(model_option, model)) return 1;

		this->application_configuration->add_model_option(model_option);
	}

	return 0;
}

int CommandLineController::parse_arguments(int argc, const char* const argv[]) {
	args::ArgumentParser parser("Bridge Model Simulation", "Application tha demonstates soft-body dynamics modeling.");
	args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });
	args::Flag simulation_help(parser, "help-simulation", "Display help for simulation commands", { 's', "help-simulation" });
	args::CompletionFlag completion(parser, { "complete" });

	args::Flag test_flag(parser, "test", "Run self-testing scenarios", { 't', "test" });
	args::ValueFlag<std::string> gtest_flag(parser, "gtest_filter", "Run self-testing scenarios", { "gtest_filter" });
	args::Flag video_flag(parser, "video", "Write simulation to video file", { 'v', "video" });

	args::PositionalList<std::string> models(parser, "models", "Simulation model, use help ");

	try
	{
		parser.ParseCLI(argc, argv);
	}
	catch (const args::Completion& e)
	{
		std::cout << e.what();
		return CommandLineController::COMPLITION;
	}
	catch (const args::Help&)
	{
		std::cout << parser;
		return CommandLineController::HELP;
	}
	catch (const args::ParseError& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return CommandLineController::ERROR;
	}

	if (simulation_help) {
		print_simulation_help();
		return CommandLineController::HELP;
	}

	if (this->parse_models(args::get(models))) {
		std::cout << "Wrong model argument" << std::endl;

		return CommandLineController::ERROR;
	}

	this->application_configuration->set_run_test_flag(test_flag);
	this->application_configuration->set_write_video_flag(video_flag);

	return CommandLineController::SUCCESS;
}
