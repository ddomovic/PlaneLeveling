#pragma once

#define PI 3.14159265359

class RandomForceApplier {
private:
	float _min_period;
	float _max_period;
	float _min_amplitude;
	float _max_amplitude;
	float _current_period;
	float _current_amplitude;
	float _reference_time;
	float _passed_time;
public:
	RandomForceApplier(float min_period, float max_period, float _min_amplitude, float max_amplitude);
	float calculate_current_force(float delta_time);
	float get_min_period();
	float get_max_period();
	float get_min_amplitude();
	float get_max_amplitude();
	float get_current_period();
	float get_current_amplitude();
	float get_reference_time();
	float get_passed_time();
	void set_min_period(float min_period);
	void set_max_period(float max_period);
	void set_min_amplitude(float min_amplitude);
	void set_max_amplitude(float max_amplitude);
	void set_current_period(float current_period);
	void set_current_amplitude(float current_amplitude);
	void set_reference_time(float reference_time);
	void set_passed_time(float passed_time);
	void add_passed_time(float delta_time);
};