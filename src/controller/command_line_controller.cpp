#include "controller/command_line_controller.h"

#include "model/aplication_configuration.h"
#include "model/configuration/simulation_option.h"
#include "factory/simulation_context_factory.h"

#include <iostream>
#include <args.hxx>

const int CommandLineController::SUCCESS = 0;
const int CommandLineController::COMPLITION = 1;
const int CommandLineController::HELP = 2;
const int CommandLineController::ERROR = 3;


CommandLineController::CommandLineController(std::shared_ptr<ApplicationConfiguration> application_configuration, std::shared_ptr<SimulationContextFactory> simulation_context_factory)
{
	this->application_configuration = application_configuration;
	this->simulation_context_factory = simulation_context_factory;
}

void CommandLineController::print_simulation_help() {
	std::cout << "Simulation model help" << std::endl;
	std::cout << std::endl;
	std::cout << "  cpp-bridge-v5.exe [models...] {OPTIONS}" << std::endl;
	std::cout << std::endl;
	std::cout << "  Format for 'models' option: {contollers}:{bridges}:{simulation-types}" << std::endl;
	std::cout << "     Format for 'contollers'       - controller1[,controller1,..] | *" << std::endl;
	std::cout << "     Format for 'bridges'          - bridge1[,bridge2,..] | *" << std::endl;
	std::cout << "     Format for 'simulation-types' - type1[,type2,..] | *" << std::endl;
	std::cout << std::endl;
	std::cout << "  Example: *:rope,pandulum:100x" << std::endl;
	std::cout << std::endl;
	
	std::cout << "  Contrllers:" << std::endl;
	for (auto controler : this->simulation_context_factory->get_controller_types()) {
		std::cout << "    " << controler << std::endl;
	}
	std::cout << std::endl;

	std::cout << "  Bridges:" << std::endl;
	for (auto bridge_model: this->simulation_context_factory->get_bridge_models()) {
		std::cout << "    " << bridge_model << std::endl;
	}
	std::cout << std::endl;

	std::cout << "  Simulation types:" << std::endl;
	for (auto simulation_type : this->simulation_context_factory->get_simulation_types()) {
		std::cout << "    " << simulation_type << std::endl;
	}
	std::cout << std::endl;
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

int parse_controllers(std::shared_ptr<SimulationOption> model_option, const std::string& string_value) {
	std::vector<std::string> vector;
	if (split_comma_string(string_value, vector)) return 1;

	for (const auto value : vector) {
		model_option->add_controller_type(value);
	}

	return 0;
}

int parse_bridge_models(std::shared_ptr<SimulationOption> model_option, const std::string string_value) {
	std::vector<std::string> vector;
	if (split_comma_string(string_value, vector)) return 1;

	for (const auto value : vector) {
		model_option->add_bridge_model(value);
	}

	return 0;
}

int parse_simulation_types(std::shared_ptr<SimulationOption> model_option, const std::string string_value) {
	std::vector<std::string> vector;
	if (split_comma_string(string_value, vector)) return 1;

	for (const auto value : vector) {
		model_option->add_simulation_type(value);
	}

	return 0;
}

int CommandLineController::parse_simulations(const std::vector<std::string>& simulations) {
	
	for (const auto simulation : simulations) {

		std::stringstream stream(simulation);

		std::string controller_types;
		std::string bridge_model;
		std::string simulatio_type;

		if (stream.eof()) return 1;
		std::getline(stream, controller_types, ':');

		if (stream.eof()) return 1;
		std::getline(stream, bridge_model, ':');

		if (stream.eof()) return 1;
		std::getline(stream, simulatio_type);

		std::shared_ptr<SimulationOption> simulation_option(new SimulationOption());

		if (parse_controllers(simulation_option, controller_types)) return 1;
		if (parse_bridge_models(simulation_option, bridge_model)) return 1;
		if (parse_simulation_types(simulation_option, simulatio_type)) return 1;

		this->application_configuration->add_simulation_option(simulation_option);
	}

	return 0;
}

int CommandLineController::parse_arguments(int argc, const char* const argv[]) {
	args::ArgumentParser parser("Bridge Model Simulation", "Application that demonstates soft-body dynamics modeling.");
	args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });
	args::Flag simulation_help(parser, "help-simulation", "Display help for simulation commands", { 's', "help-simulation" });
	args::CompletionFlag completion(parser, { "complete" });

	args::Flag test_flag(parser, "test", "Run self-testing scenarios", { 't', "test" });
	args::ValueFlag<std::string> gtest_flag(parser, "gtest_filter", "Run self-testing scenarios", { "gtest_filter" });
	args::Flag video_flag(parser, "video", "Write simulation to video file", { 'v', "video" });

	args::PositionalList<std::string> simulations(parser, "simulations", "Simulation models, use help-simulation for more information ");

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

	if (this->parse_simulations(args::get(simulations))) {
		std::cout << "Wrong model argument" << std::endl;

		return CommandLineController::ERROR;
	}

	this->application_configuration->set_run_test_flag(test_flag);
	this->application_configuration->set_write_video_flag(video_flag);

	return CommandLineController::SUCCESS;
}
