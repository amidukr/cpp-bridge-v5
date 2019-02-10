#include "model/bridge_model.h"
#include "model/simulation_model.h"
#include "model/sample_data_model.h"

const std::string SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION = "optimal-with-delay";
const std::string SampleDataModel::TEN_TIME_FACTOR_SIMULATION = "10x-time-factor";

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

	simulation_model->set_iteration_delay(10);
	simulation_model->set_time_factor(1);

	simulation_model->set_gravity(Eigen::Vector2d(0, -9.8));

	simulation_model->set_spring_characteristic(1.0);
	simulation_model->set_dumping_ration(0.9);

	return simulation_model;
}

std::unique_ptr<SimulationModel> create_ten_time_factor() {
	std::unique_ptr<SimulationModel> simulation_model(new SimulationModel());

	simulation_model->set_iteration_delay(10);
	simulation_model->set_time_factor(10);

	simulation_model->set_gravity(Eigen::Vector2d(0, -9.8));

	simulation_model->set_spring_characteristic(1.0);
	simulation_model->set_dumping_ration(0.5);

	return simulation_model;
}


std::unique_ptr<SimulationModel> SampleDataModel::load_simulation_model(std::string model_name) {
	if (model_name == SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION) {
		return create_optimal_with_delay();
	}

	if (model_name == SampleDataModel::TEN_TIME_FACTOR_SIMULATION) {
		return create_ten_time_factor();
	}

	throw "simulation setting not found";
}

//-------------- Brdige Model --------------

std::unique_ptr<BridgeModel> create_square_bridge() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& junction_bl = bridge_model->add_junction(20, 20);
	Junction& junction_br = bridge_model->add_junction(40, 20);
	Junction& junction_tl = bridge_model->add_hard_junction(20, 40);
	Junction& junction_tr = bridge_model->add_junction(40, 40);

	bridge_model->add_girder(junction_bl, junction_br);
	bridge_model->add_girder(junction_br, junction_tr);
	bridge_model->add_girder(junction_tl, junction_tr);
	bridge_model->add_girder(junction_tl, junction_bl);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_heart_bridge() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& junction_hard = bridge_model->add_hard_junction(0, 0);
	Junction& junction_l1 = bridge_model->add_junction(-5, 5);
	Junction& junction_r1 = bridge_model->add_junction(5, 5);
	Junction& junction_l2 = bridge_model->add_junction(-10, 0);
	Junction& junction_r2 = bridge_model->add_junction(10, 0);
	Junction& junction_bottom = bridge_model->add_junction(0, -10);



	bridge_model->add_girder(junction_hard, junction_l1);
	bridge_model->add_girder(junction_hard, junction_r1);

	bridge_model->add_girder(junction_l1, junction_l2);
	bridge_model->add_girder(junction_r1, junction_r2);

	bridge_model->add_girder(junction_l2, junction_bottom);
	bridge_model->add_girder(junction_r2, junction_bottom);

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_line_up() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	bridge_model->set_prefered_scale_out_factor(10);

	Junction& bottom = bridge_model->add_hard_junction(0, 0);

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

	bridge_model->set_prefered_scale_out_factor(10);

	Junction& bottom = bridge_model->add_hard_junction(0, 0);

	Junction* prev = &bottom;
	for (int i = 0; i < 20; i++) {
		Junction& p = bridge_model->add_junction(i, i);

		bridge_model->add_girder(*prev, p);

		prev = &p;
	}

	return bridge_model;
}

std::unique_ptr<BridgeModel> create_triangle_grid() {
	std::unique_ptr<BridgeModel> bridge_model(new BridgeModel());

	//bridge_model->set_prefered_scale_out_factor(5);
	
	const int N = 3;

	Junction* junctions[N][N];
	Junction& hard = bridge_model->add_hard_junction(0, 0);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			junctions[i][j] = &bridge_model->add_junction(i - N/2, j + 1);
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
		bridge_model->add_girder(*junctions[i][0], hard);
	}

	return bridge_model;
}


std::unique_ptr<BridgeModel> SampleDataModel::load_bridge_model(std::string model_name) {
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
