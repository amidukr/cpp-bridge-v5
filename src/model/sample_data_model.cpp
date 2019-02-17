#include "model/bridge_model.h"
#include "model/simulation_model.h"

#include "model/sample_data_model.h"

const std::string SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION = "optimal-with-delay";
const std::string SampleDataModel::TEN_TIME_LOW_DUMPING = "10x-low-dumping";
const std::string SampleDataModel::TEN_TIME_FACTOR_SIMULATION = "10x-time-factor";
const std::string SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION = "100x-time-factor";

const std::string SampleDataModel::ROPE_BRIDGE = "rope";
const std::string SampleDataModel::SWING_BRIDGE = "swing";
const std::string SampleDataModel::PANDULUM_BRIDGE = "pandulum";
const std::string SampleDataModel::SQUARE_BRIDGE = "square";
const std::string SampleDataModel::HEART_BRIDGE = "heart";
const std::string SampleDataModel::LINE_UP = "line-up";
const std::string SampleDataModel::LINE_DIAGONAL = "line-diagonal";
const std::string SampleDataModel::TRIANGLE_GRID = "triangle-grid";




SampleDataModel::SampleDataModel() {

}

//-------------- Simulation Settings --------------

std::unique_ptr<SimulationModel> create_optimal_with_delay() {
	std::unique_ptr<SimulationModel> simulation_model(new SimulationModel());

	simulation_model->set_iteration_delay(1);
	simulation_model->set_time_factor(0.1);

	simulation_model->set_gravity(Eigen::Vector2d(0, -9.8));

	simulation_model->set_spring_characteristic(1.0);
	simulation_model->set_dumping_ratio(1);

	return simulation_model;
}

std::unique_ptr<SimulationModel> create_ten_time_low_dumping() {
	std::unique_ptr<SimulationModel> simulation_model = create_optimal_with_delay();

	simulation_model->set_time_factor(100);
	simulation_model->set_dumping_ratio(0.99);

	return simulation_model;
}


std::unique_ptr<SimulationModel> create_ten_time_factor() {
	std::unique_ptr<SimulationModel> simulation_model = create_optimal_with_delay();

	simulation_model->set_time_factor(10);

	return simulation_model;
}

std::unique_ptr<SimulationModel> create_hundred_time_factor() {
	std::unique_ptr<SimulationModel> simulation_model = create_optimal_with_delay();

	simulation_model->set_time_factor(100);

	return simulation_model;
}


std::unique_ptr<SimulationModel> SampleDataModel::load_simulation_model(std::string model_name) {
	if (model_name == SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION) {
		return create_optimal_with_delay();
	}

	if (model_name == SampleDataModel::TEN_TIME_LOW_DUMPING) {
		return create_ten_time_low_dumping();
	}

	if (model_name == SampleDataModel::TEN_TIME_FACTOR_SIMULATION) {
		return create_ten_time_factor();
	}

	if (model_name == SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION) {
		return create_hundred_time_factor();
	}

	throw "simulation setting not found";
}

//-------------- Brdige Model --------------

std::unique_ptr<BridgeModel> create_rope_bridge() {

	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& left_fixed = bridge_model->add_fixed_junction(0, 0);
	Junction& right_fixed = bridge_model->add_fixed_junction(10, 0);

	Junction* prev = &left_fixed;
	for (int i = 1; i < 10; i++) {
		Junction& j = bridge_model->add_junction(i, 0);
		bridge_model->add_girder(*prev, j);
		prev = &j;
	}

	bridge_model->add_girder(*prev, right_fixed);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_swing_bridge() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& left_fixed = bridge_model->add_fixed_junction(0, 0);
	Junction& right_fixed = bridge_model->add_fixed_junction(10, 0);

	Junction& left_floating = bridge_model->add_junction(-5, 5);
	Junction& right_floating = bridge_model->add_junction(5, 5);

	bridge_model->add_girder(left_fixed, left_floating);
	bridge_model->add_girder(left_floating, right_floating);
	bridge_model->add_girder(right_floating, right_fixed);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_pandulum_bridge() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& fixed = bridge_model->add_fixed_junction(0, 0);
	Junction& floating = bridge_model->add_junction(4, -4);

	bridge_model->add_girder(fixed, floating);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_square_bridge() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& junction_bl = bridge_model->add_junction(20, 20);
	Junction& junction_br = bridge_model->add_junction(40, 20);
	Junction& junction_tl = bridge_model->add_fixed_junction(20, 40);
	Junction& junction_tr = bridge_model->add_junction(40, 40);

	bridge_model->add_girder(junction_bl, junction_br);
	bridge_model->add_girder(junction_br, junction_tr);
	bridge_model->add_girder(junction_tl, junction_tr);
	bridge_model->add_girder(junction_tl, junction_bl);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_heart_bridge() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& junction_fixed = bridge_model->add_fixed_junction(0, 0);
	Junction& junction_l1 = bridge_model->add_junction(-5, 5);
	Junction& junction_r1 = bridge_model->add_junction(5, 5);
	Junction& junction_l2 = bridge_model->add_junction(-10, 0);
	Junction& junction_r2 = bridge_model->add_junction(10, 0);
	Junction& junction_bottom = bridge_model->add_junction(0, -10);



	bridge_model->add_girder(junction_fixed, junction_l1);
	bridge_model->add_girder(junction_fixed, junction_r1);

	bridge_model->add_girder(junction_l1, junction_l2);
	bridge_model->add_girder(junction_r1, junction_r2);

	bridge_model->add_girder(junction_l2, junction_bottom);
	bridge_model->add_girder(junction_r2, junction_bottom);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_line_up() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	bridge_model->set_prefered_scale_out_factor(10);

	Junction& bottom = bridge_model->add_fixed_junction(0, 0);

	Junction* prev = &bottom;
	for (int i = 0; i < 20; i++) {
		Junction& p = bridge_model->add_junction(0, i);

		bridge_model->add_girder(*prev, p);

		prev = &p;
	}

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_line_diagonal() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	bridge_model->set_prefered_scale_out_factor(5);

	Junction& bottom = bridge_model->add_fixed_junction(0, 0);

	Junction* prev = &bottom;
	for (int i = 1; i < 20; i++) {
		Junction& p = bridge_model->add_junction(20*i, 20 * i);

		bridge_model->add_girder(*prev, p);

		prev = &p;
	}

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_triangle_grid() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	bridge_model->set_prefered_scale_out_factor(7);
	
	const int N = 5;

	Junction* junctions[N][N];
	Junction& fixed = bridge_model->add_fixed_junction(0, 0);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			junctions[i][j] = &bridge_model->add_junction(i, j + 1);
		}
	}

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			bridge_model->add_girder(*junctions[i][j], *junctions[i-1][j]);
			bridge_model->add_girder(*junctions[i][j], *junctions[i][j-1]);
			bridge_model->add_girder(*junctions[i-1][j-1], *junctions[i-1][j]);
			bridge_model->add_girder(*junctions[i-1][j-1], *junctions[i][j-1]);

			bridge_model->add_girder(*junctions[i][j], *junctions[i-1][j-1]);
			bridge_model->add_girder(*junctions[i-1][j], *junctions[i][j - 1]);
		}
	}

	for (int i = 0; i < N; i++) {
		bridge_model->add_girder(*junctions[i][0], fixed);
	}

	return bridge_model;
}


std::unique_ptr<BridgeModel> SampleDataModel::load_bridge_model(std::string model_name) {

	if (model_name == SampleDataModel::ROPE_BRIDGE) {
		return create_rope_bridge();
	}

	if (model_name == SampleDataModel::SWING_BRIDGE) {
		return create_swing_bridge();
	}
		
	if (model_name == SampleDataModel::PANDULUM_BRIDGE) {
		return create_pandulum_bridge();
	}

	if (model_name == SampleDataModel::HEART_BRIDGE) {
		return create_heart_bridge();
	}

	if (model_name == SampleDataModel::SQUARE_BRIDGE) {
		return create_square_bridge();
	}

	if (model_name == SampleDataModel::LINE_UP) {
		return create_line_up();
	}

	if (model_name == SampleDataModel::LINE_DIAGONAL) {
		return create_line_diagonal();
	}

	if (model_name == SampleDataModel::TRIANGLE_GRID) {
		return create_triangle_grid();
	}

	throw "bridge model not found";
}
