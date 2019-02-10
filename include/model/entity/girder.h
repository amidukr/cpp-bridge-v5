#ifndef GIRDER_H
#define GIRDER_H

class Girder {

	int index;
	int junction1_id;
	int junction2_id;

public:
	Girder(int index, int junction1_id, int junction2_id);

	int get_index();
	int get_junction1_id();
	int get_junction2_id();

private:
	// Disable copy constructor
	Girder(const Girder&); // no implementation 
	Girder& operator=(const Girder&); // no implementation
};

#endif /*GIRDER_H*/