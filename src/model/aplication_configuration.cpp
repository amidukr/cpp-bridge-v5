#include "model/aplication_configuration.h"

#include <cxxopts.hpp>
#include <args.hxx>
#include <iostream>

ApplicationConfiguration::ApplicationConfiguration()
{
}

bool ApplicationConfiguration::get_write_video_flag() const {
	return this->write_video_flag;
}

bool ApplicationConfiguration::get_run_test_flag() const {
	return this->run_test_flag;
}

int ApplicationConfiguration::parse_arguments(int argc, char* argv[]) {
	args::ArgumentParser parser("Bridge", "Application for soft-body dynamics modeling.");
	args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });
	args::CompletionFlag completion(parser, { "complete" });

	args::Flag test_flag(parser, "test", "Run self-testing scenarios", { 't', "test" });
	args::Flag video_flag(parser, "video", "Write simulation to video file", { 'v', "video" });

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

	this->run_test_flag = test_flag;
	this->write_video_flag = video_flag;

	return 0;
}
