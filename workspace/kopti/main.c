#include <stdio.h>
#include <stdlib.h>

#include "nsp_core_common.h"
#include "nsp_base_api.h"
#include "nsp_device_api.h"
#include "nsp_core_api.h"
#include "nsp_app_color_api.h"

#include "nsp_device_def.h"

char* g_str_sensor_id = "sensor_Y8585-1-11-13-0";
char* g_sensor_cal_file_path = "./config/sensor_Y8585-1-11-13-0.dat";

int measurement();

int main(int argc, char **argv)
{ 
	while(1)
	{
		// Input Working flag to Start
		while(1) 
		{
		
			
			
		}

	}
	return 0;
}

int measurement()
{
	int 	current_device_index = 0;
	int 	total_num_of_sensor = 0;
	int 	ret_val =0;

	double 	sensor_data_buf[SENSOR_DATA_SIZE];
	double 	background_data_buf[SENSOR_DATA_SIZE];

	int	frame_averages = 50;

	try
	{
		char str_sensor_id1[SENSOR_ID_STRING_LENGTH];
		char str_sensor_id2[SENSOR_ID_STRING_LENGTH];

		// open(connect)
		if( ret_val = duConnect() <= 0 )
		{
			throw nsp_base_exception(cc_ec_fail_to_connect_device);
		}
		// total count of device
		total_num_of_sensors = duGetTotalSensors();

		// get sensor ID
		duGetSensorID(str_sensor_id1);

		// Initialize Core Spectrum C API
		if( csCreate() != NSP_RETURN_VALUE_SUCCESS )
		{
			throw nsp_base_exception(cc_ec_fail_to_create_core_spectrum_obj);
		}
		
		// add one sensor to active sensor list
		char sensor_cal_file_path[1024];
		sprintf(sensor_cal_file_path, "./confg/sensor_%s.dat", str_sensor_id1);
		int total_count_of_active_sensors = csRegister(sensor_cal_file_path);
		if( total_count_of_active_sensors == 0)
		{
			throw nsp_base_exception(cc_ec_fail_to_add_sensor_to_active_sensor_list);
		}
		if( ret_val <= 0 )
		{
			throw nsp_base_exception(cc_ec_fail_to_load_sensor_cal_data);
		}

		// get sensor ID from sensor calibration data for matching
		int id_size = csGetSensorID(str_sensor_id2);
		if( id_size <= 0 )
		{
			return NSP_RETURN_VALUE_FAILURE;
		}

		// check if sensor ID is matched between device and sensor(device) clibration data.
		if( strncmp(str_sensor_id1, str_sensor_id2, SENSOR_ID_STRInG_LENGTH) == 0 )
		{
			// Sensor is matched
		}
		else
		{
			// Sensor is not matched
		}

		// Initialize 'application color' interface
		ret_val = acInitialize();
		if( ret_val <= 0 )
		{
			throw nsp_base_exception(cc_ec_fail_to_initialize_color_object);
		}

		//////////////////////////////////////// Set sensor params

		//// Activate a specific device(sensor)
		ret_val = duActivateSensorWithIndex(0);
		if( ret_val == cc_ec_undefined_fail )
		{
			return (int)cc_ec_undefined_fail;
		}

		//// Activate sensor calibration data with sensor ID
		//ret_val = csActivateSensorWithID(str_sensor_id1); // physical sensor id

		//// Get ADC settings info. from sensor calibration data.
		int adc_gain = 0, adc_range = 0;
		csGetSensorParameters( &adc_gain, &adc_range );

		//// Change ADC settings of device
		duSetSensorParameters( adc_gain, adc_range );

		//////////////////////////////////////////////////////////////////////


		////////////////////////////////// Acquire raw filter data
		
		// Activate a specific device(sensor)
		ret_val = duActivateSensorWithIndex(current_device_index);
		if( ret_val == cc_ec_undefined_fail )
		{
			return (int)cc_ec_undefined_fail;
		}

		///////////////////////////////// Get background data
		// Set/Change shutter speed(SS) of device(sensor)
		//**********************
		ret_val = duSetShutterSpeed(new_shtter_speed);
	}
	catch(nsp_base_exception &e){
		csDestroy();
		acFinalize();
		duDisconnect();

		return (int)-e.error_code;
	}
	catch(...){
		csDestroy();
		acFinalize();
		duDisconnect();

		return NSP_RETURN_VALUE_FAILURE;
	}
	return 0;
}

