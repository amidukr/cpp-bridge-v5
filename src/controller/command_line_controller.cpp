#include "controller/command_line_controller.h"

#include "model/aplication_configuration.h"

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

int CommandLineController::parse_arguments(int argc, char* argv[]) {
	args::ArgumentParser parser("Bridge Model Simulation", "Application tha demonstates soft-body dynamics modeling.");
	args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });
	args::Flag simulation_help(parser, "help-simulation", "Display help for simulation commands", { 's', "help-simulation" });
	args::CompletionFlag completion(parser, { "complete" });

	args::Flag test_flag(parser, "test", "Run self-testing scenarios", { 't', "test" });
	args::Flag video_flag(parser, "video", "Write simulation to video file", { 'v', "video" });

	args::PositionalList<std::string> models(parser, "models", "Simulation model, use help ");



	try
	{
		parser.ParseCLI(argc, argv);
	}
	catch (const args::Completion& e)
	{
		std::cout << e.what();
		return 0;
	}
	catch (const args::Help&)
	{
		std::cout << parser;
		return 1;
	}
	catch (const args::ParseError& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}

	if (simulation_help) {
		print_simulation_help();
		return 1;
	}

	this->application_configuration->set_run_test_flag(test_flag);
	this->application_configuration->set_write_video_flag(video_flag);

	return 0;
}