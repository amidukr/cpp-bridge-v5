#include <gtest/gtest.h>

#include "controller/command_line_controller.h"
#include "model/application_configuration.h"
#include "model/configuration/simulation_option.h"
#include "factory/simulation_context_factory.h"

#include <memory>

bool compare_application_configurations(ApplicationConfiguration& a, ApplicationConfiguration& b) {
	return true;
}

TEST(CommandLineControllerTest, test_defaults) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	std::shared_ptr<SimulationContextFactory> simulation_context_factory;
	CommandLineController command_line_controller{ application_configuration, simulation_context_factory };

	const char* arguments[] = { "/command-executable"};

	command_line_controller.parse_arguments(1, arguments);

	ASSERT_FALSE(application_configuration->get_run_test_flag());
	ASSERT_FALSE(application_configuration->get_write_video_flag());
}

TEST(CommandLineControllerTest, test_flags) {
	std::shared_ptr<SimulationContextFactory> simulation_context_factory;
	std::shared_ptr<ApplicationConfiguration> application_configuration1(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration2(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration3(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration4(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration5(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration6(new ApplicationConfiguration());

	CommandLineController command_line_controller1{ application_configuration1, simulation_context_factory };
	CommandLineController command_line_controller2{ application_configuration2, simulation_context_factory };
	CommandLineController command_line_controller3{ application_configuration3, simulation_context_factory };
	CommandLineController command_line_controller4{ application_configuration4, simulation_context_factory };
	CommandLineController command_line_controller5{ application_configuration5, simulation_context_factory };
	CommandLineController command_line_controller6{ application_configuration6, simulation_context_factory };

	const char* arguments1[] = { "/command-executable", "-t", "-v" };
	const char* arguments2[] = { "/command-executable", "--test", "--video" };
	const char* arguments3[] = { "/command-executable", "-t" };
	const char* arguments4[] = { "/command-executable", "-v" };
	const char* arguments5[] = { "/command-executable", "--test" };
	const char* arguments6[] = { "/command-executable", "--video" };

	ASSERT_EQ(command_line_controller1.parse_arguments(3, arguments1), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller2.parse_arguments(3, arguments2), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller3.parse_arguments(2, arguments3), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller4.parse_arguments(2, arguments4), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller5.parse_arguments(2, arguments5), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller6.parse_arguments(2, arguments6), CommandLineController::SUCCESS);

	ASSERT_TRUE(application_configuration1->get_run_test_flag());
	ASSERT_TRUE(application_configuration1->get_write_video_flag());

	ASSERT_TRUE(application_configuration2->get_run_test_flag());
	ASSERT_TRUE(application_configuration2->get_write_video_flag());

	ASSERT_TRUE(application_configuration3->get_run_test_flag());
	ASSERT_FALSE(application_configuration3->get_write_video_flag());

	ASSERT_FALSE(application_configuration4->get_run_test_flag());
	ASSERT_TRUE(application_configuration4->get_write_video_flag());

	ASSERT_TRUE(application_configuration5->get_run_test_flag());
	ASSERT_FALSE(application_configuration5->get_write_video_flag());

	ASSERT_FALSE(application_configuration6->get_run_test_flag());
	ASSERT_TRUE(application_configuration6->get_write_video_flag());
} 

TEST(CommandLineControllerTest, test_help) {
	std::shared_ptr<ApplicationConfiguration> application_configuration1(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration2(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration3(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration4(new ApplicationConfiguration());

	std::shared_ptr<SimulationContextFactory> simulation_context_factory(new SimulationContextFactory(application_configuration1));
	
	CommandLineController command_line_controller1{ application_configuration1, simulation_context_factory };
	CommandLineController command_line_controller2{ application_configuration2, simulation_context_factory };
	CommandLineController command_line_controller3{ application_configuration3, simulation_context_factory };
	CommandLineController command_line_controller4{ application_configuration4, simulation_context_factory };
	
	const char* arguments1[] = { "/command-executable", "-h" };
	const char* arguments2[] = { "/command-executable", "--help" };
	const char* arguments3[] = { "/command-executable", "-s" };
	const char* arguments4[] = { "/command-executable", "--help-simulation" };

	ASSERT_EQ(command_line_controller1.parse_arguments(2, arguments1), CommandLineController::HELP);
	ASSERT_EQ(command_line_controller2.parse_arguments(2, arguments2), CommandLineController::HELP);
	ASSERT_EQ(command_line_controller3.parse_arguments(2, arguments3), CommandLineController::HELP);
	ASSERT_EQ(command_line_controller4.parse_arguments(2, arguments4), CommandLineController::HELP);

	ASSERT_FALSE(application_configuration1->get_run_test_flag());
	ASSERT_FALSE(application_configuration1->get_write_video_flag());

	ASSERT_FALSE(application_configuration2->get_run_test_flag());
	ASSERT_FALSE(application_configuration2->get_write_video_flag());

	ASSERT_FALSE(application_configuration3->get_run_test_flag());
	ASSERT_FALSE(application_configuration3->get_write_video_flag());

	ASSERT_FALSE(application_configuration4->get_run_test_flag());
	ASSERT_FALSE(application_configuration4->get_write_video_flag());
}

TEST(CommandLineControllerTest, test_options) {
	std::shared_ptr<SimulationContextFactory> simulation_context_factory;
	std::shared_ptr<ApplicationConfiguration> application_configuration1(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration2(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration3(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration4(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration5(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration6(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration7(new ApplicationConfiguration());

	CommandLineController command_line_controller1{ application_configuration1, simulation_context_factory };
	CommandLineController command_line_controller2{ application_configuration2, simulation_context_factory };
	CommandLineController command_line_controller3{ application_configuration3, simulation_context_factory };
	CommandLineController command_line_controller4{ application_configuration4, simulation_context_factory };
	CommandLineController command_line_controller5{ application_configuration5, simulation_context_factory };
	CommandLineController command_line_controller6{ application_configuration6, simulation_context_factory };
	CommandLineController command_line_controller7{ application_configuration7, simulation_context_factory };

	const char* arguments1[] = { "/command-executable", "controller:map:option" };
	const char* arguments2[] = { "/command-executable", "*:map:*" };
	const char* arguments3[] = { "/command-executable", "controller1,controller2:map:option" };
	const char* arguments4[] = { "/command-executable", "controller:map1,map2,map3:option" };
	const char* arguments5[] = { "/command-executable", "controller:map:option1,option2" };
	const char* arguments6[] = { "/command-executable", "*:rope,pandulum:100x" };
	const char* arguments7[] = { "/command-executable", "-t", "controller1:map1:option1", "controller2:map2:option2" };
	
	ASSERT_EQ(command_line_controller1.parse_arguments(2, arguments1), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller2.parse_arguments(2, arguments2), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller3.parse_arguments(2, arguments3), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller4.parse_arguments(2, arguments4), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller5.parse_arguments(2, arguments5), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller6.parse_arguments(2, arguments6), CommandLineController::SUCCESS);
	ASSERT_EQ(command_line_controller7.parse_arguments(4, arguments7), CommandLineController::SUCCESS);


	ASSERT_FALSE(application_configuration1->get_run_test_flag());
	ASSERT_FALSE(application_configuration1->get_write_video_flag());
	ASSERT_EQ(application_configuration1->get_simulation_options().size(), 1);
	ASSERT_EQ(application_configuration1->get_simulation_options().at(0)->get_controller_types().size(), 1);
	ASSERT_EQ(application_configuration1->get_simulation_options().at(0)->get_bridge_models().size(), 1);
	ASSERT_EQ(application_configuration1->get_simulation_options().at(0)->get_simulatio_types().size(), 1);
	ASSERT_EQ(application_configuration1->get_simulation_options().at(0)->get_controller_types().at(0), "controller");
	ASSERT_EQ(application_configuration1->get_simulation_options().at(0)->get_bridge_models().at(0), "map");
	ASSERT_EQ(application_configuration1->get_simulation_options().at(0)->get_simulatio_types().at(0), "option");
	
	ASSERT_FALSE(application_configuration2->get_run_test_flag());
	ASSERT_FALSE(application_configuration2->get_write_video_flag());
	ASSERT_EQ(application_configuration2->get_simulation_options().size(), 1);
	ASSERT_EQ(application_configuration2->get_simulation_options().at(0)->get_controller_types().size(), 1);
	ASSERT_EQ(application_configuration2->get_simulation_options().at(0)->get_bridge_models().size(), 1);
	ASSERT_EQ(application_configuration2->get_simulation_options().at(0)->get_simulatio_types().size(), 1);
	ASSERT_EQ(application_configuration2->get_simulation_options().at(0)->get_controller_types().at(0), "*");
	ASSERT_EQ(application_configuration2->get_simulation_options().at(0)->get_bridge_models().at(0), "map");
	ASSERT_EQ(application_configuration2->get_simulation_options().at(0)->get_simulatio_types().at(0), "*");

	ASSERT_FALSE(application_configuration3->get_run_test_flag());
	ASSERT_FALSE(application_configuration3->get_write_video_flag());
	ASSERT_EQ(application_configuration3->get_simulation_options().size(), 1);
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_controller_types().size(), 2);
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_bridge_models().size(), 1);
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_simulatio_types().size(), 1);
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_controller_types().at(0), "controller1");
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_controller_types().at(1), "controller2");
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_bridge_models().at(0), "map");
	ASSERT_EQ(application_configuration3->get_simulation_options().at(0)->get_simulatio_types().at(0), "option");

	ASSERT_FALSE(application_configuration4->get_run_test_flag());
	ASSERT_FALSE(application_configuration4->get_write_video_flag());
	ASSERT_EQ(application_configuration4->get_simulation_options().size(), 1);
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_controller_types().size(), 1);
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_bridge_models().size(), 3);
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_simulatio_types().size(), 1);
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_controller_types().at(0), "controller");
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_bridge_models().at(0), "map1");
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_bridge_models().at(1), "map2");
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_bridge_models().at(2), "map3");
	ASSERT_EQ(application_configuration4->get_simulation_options().at(0)->get_simulatio_types().at(0), "option");

	ASSERT_FALSE(application_configuration5->get_run_test_flag());
	ASSERT_FALSE(application_configuration5->get_write_video_flag());
	ASSERT_EQ(application_configuration5->get_simulation_options().size(), 1);
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_controller_types().size(), 1);
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_bridge_models().size(), 1);
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_simulatio_types().size(), 2);
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_controller_types().at(0), "controller");
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_bridge_models().at(0), "map");
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_simulatio_types().at(0), "option1");
	ASSERT_EQ(application_configuration5->get_simulation_options().at(0)->get_simulatio_types().at(1), "option2");

	ASSERT_FALSE(application_configuration6->get_run_test_flag());
	ASSERT_FALSE(application_configuration6->get_write_video_flag());
	ASSERT_EQ(application_configuration6->get_simulation_options().size(), 1);
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_controller_types().size(), 1);
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_bridge_models().size(), 2);
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_simulatio_types().size(), 1);
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_controller_types().at(0), "*");
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_bridge_models().at(0), "rope");
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_bridge_models().at(1), "pandulum");
	ASSERT_EQ(application_configuration6->get_simulation_options().at(0)->get_simulatio_types().at(0), "100x");

	ASSERT_TRUE(application_configuration7->get_run_test_flag());
	ASSERT_FALSE(application_configuration7->get_write_video_flag());
	ASSERT_EQ(application_configuration7->get_simulation_options().size(), 2);
	{
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_controller_types().size(), 1);
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_bridge_models().size(), 1);
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_simulatio_types().size(), 1);
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_controller_types().at(0), "controller1");
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_bridge_models().at(0), "map1");
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_simulatio_types().at(0), "option1");
		ASSERT_EQ(application_configuration7->get_simulation_options().at(0)->get_controller_types().size(), 1);
	}
	{
		ASSERT_EQ(application_configuration7->get_simulation_options().at(1)->get_controller_types().size(), 1);
		ASSERT_EQ(application_configuration7->get_simulation_options().at(1)->get_bridge_models().size(), 1);
		ASSERT_EQ(application_configuration7->get_simulation_options().at(1)->get_simulatio_types().size(), 1);
		ASSERT_EQ(application_configuration7->get_simulation_options().at(1)->get_controller_types().at(0), "controller2");
		ASSERT_EQ(application_configuration7->get_simulation_options().at(1)->get_bridge_models().at(0), "map2");
		ASSERT_EQ(application_configuration7->get_simulation_options().at(1)->get_simulatio_types().at(0), "option2");
	}
}

TEST(CommandLineControllerTest, test_wrong_arguments) {
	std::shared_ptr<SimulationContextFactory> simulation_context_factory;
	std::shared_ptr<ApplicationConfiguration> application_configuration1(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration2(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration3(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration4(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration5(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration6(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration7(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration8(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration9(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration10(new ApplicationConfiguration());
	std::shared_ptr<ApplicationConfiguration> application_configuration11(new ApplicationConfiguration());
	
	CommandLineController command_line_controller1{ application_configuration1, simulation_context_factory };
	CommandLineController command_line_controller2{ application_configuration2, simulation_context_factory };
	CommandLineController command_line_controller3{ application_configuration3, simulation_context_factory };
	CommandLineController command_line_controller4{ application_configuration4, simulation_context_factory };
	CommandLineController command_line_controller5{ application_configuration5, simulation_context_factory };
	CommandLineController command_line_controller6{ application_configuration6, simulation_context_factory };
	CommandLineController command_line_controller7{ application_configuration7, simulation_context_factory };
	CommandLineController command_line_controller8{ application_configuration8, simulation_context_factory };
	CommandLineController command_line_controller9{ application_configuration9, simulation_context_factory };
	CommandLineController command_line_controller10{ application_configuration10, simulation_context_factory };
	CommandLineController command_line_controller11{ application_configuration11, simulation_context_factory };
	
	const char* arguments1[] = { "/command-executable", "-w" };
	const char* arguments2[] = { "/command-executable", "--wrong-argument"};
	const char* arguments3[] = { "/command-executable", "-t", "-w" };
	const char* arguments4[] = { "/command-executable", "controller" };
	const char* arguments5[] = { "/command-executable", "controller:" };
	const char* arguments6[] = { "/command-executable", "conntroller:map" };
	const char* arguments7[] = { "/command-executable", "conntroller:map:" };
	const char* arguments8[] = { "/command-executable", "conntroller::" };
	const char* arguments9[] = { "/command-executable", "conntroller,:map:option" };
	const char* arguments10[] = { "/command-executable", "conntroller,*:map:option" };
	const char* arguments11[] = { "/command-executable", "::" };

	ASSERT_EQ(command_line_controller1.parse_arguments(3, arguments1), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller2.parse_arguments(3, arguments2), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller3.parse_arguments(3, arguments3), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller4.parse_arguments(2, arguments4), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller5.parse_arguments(2, arguments5), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller6.parse_arguments(2, arguments6), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller7.parse_arguments(2, arguments7), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller8.parse_arguments(2, arguments8), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller9.parse_arguments(2, arguments9), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller10.parse_arguments(2, arguments10), CommandLineController::ERROR);
	ASSERT_EQ(command_line_controller11.parse_arguments(2, arguments11), CommandLineController::ERROR);
	
	ASSERT_FALSE(application_configuration1->get_run_test_flag());
	ASSERT_FALSE(application_configuration1->get_write_video_flag());

	ASSERT_FALSE(application_configuration2->get_run_test_flag());
	ASSERT_FALSE(application_configuration2->get_write_video_flag());

	ASSERT_FALSE(application_configuration3->get_run_test_flag());
	ASSERT_FALSE(application_configuration3->get_write_video_flag());

	ASSERT_FALSE(application_configuration4->get_run_test_flag());
	ASSERT_FALSE(application_configuration4->get_write_video_flag());

	ASSERT_FALSE(application_configuration5->get_run_test_flag());
	ASSERT_FALSE(application_configuration5->get_write_video_flag());

	ASSERT_FALSE(application_configuration6->get_run_test_flag());
	ASSERT_FALSE(application_configuration6->get_write_video_flag());

	ASSERT_FALSE(application_configuration7->get_run_test_flag());
	ASSERT_FALSE(application_configuration7->get_write_video_flag());

	ASSERT_FALSE(application_configuration8->get_run_test_flag());
	ASSERT_FALSE(application_configuration8->get_write_video_flag());

	ASSERT_FALSE(application_configuration9->get_run_test_flag());
	ASSERT_FALSE(application_configuration9->get_write_video_flag());

	ASSERT_FALSE(application_configuration10->get_run_test_flag());
	ASSERT_FALSE(application_configuration10->get_write_video_flag());

	ASSERT_FALSE(application_configuration11->get_run_test_flag());
	ASSERT_FALSE(application_configuration11->get_write_video_flag());
}
