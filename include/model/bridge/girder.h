#ifndef GIRDER_H
#define GIRDER_H

class Girder {

	int index;
	int floating_index;

	int junction1_id;
	int junction2_id;
	double original_size;

public:
	Girder(int index, int floating_index, double original_size, int junction1_id, int junction2_id);

	int get_index();
	int get_floating_index();

	double get_original_size();

	int get_junction1_id();
	int get_junction2_id();

private:
	// Disable copy constructor
	Girder(const Girder&); // no implementation 
	Girder& operator=(const Girder&); // no implementation
};

#endif /*GIRDER_H*/