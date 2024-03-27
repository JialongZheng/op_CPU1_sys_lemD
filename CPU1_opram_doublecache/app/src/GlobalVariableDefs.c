


#include "Global_struct.h"
#include "Dev_Init.h"
#include "Const_Defines.h"
#include "database.h"
#include "INV_Control.h"
#include "ModbusSlave.h"


struct RUN_DATA RunData;
struct PARA_DATA ParaData;

INV_CONTROL_OBJ Inv_controlobj;

MODBUS_COM_SEVER_OBJ ModbusComServer;

MODBUS_COM_SEVER_OBJ ModbusComServerc;

struct MAIN_LOOP m_loop;

ADC_OBJ AdcObj = ADC_OBJ_DEFAULTS;

struct ADC_GAIN AdcGain;

struct ADC_CH_ZERO AdcChZero = AdChZeroDefaults;

EX_ADC_OBJ ExAdcObj;

struct EX_ADC_GAIN ExAdcGain;

struct EX_ADC_CH_ZERO ExAdcChZero = ExAdChZeroDefaults;

TEMPERATURE_OBJ Temper_muduleA_obj = TEMPERATURE_OBJ_DEFAULTS;
TEMPERATURE_OBJ Temper_muduleB_obj = TEMPERATURE_OBJ_DEFAULTS;
TEMPERATURE_OBJ Temper_muduleC_obj = TEMPERATURE_OBJ_DEFAULTS;
TEMPERATURE_OBJ Temper_ambient_obj = TEMPERATURE_OBJ_DEFAULTS;
TEMPERATURE_OBJ Temper_ambient1_obj = TEMPERATURE_OBJ_DEFAULTS;
TEMPERATURE_OBJ Temper_SCR_obj = TEMPERATURE_OBJ_DEFAULTS;

MODULE_TEMP_CALC  moduleA_TEMP  = MODULE_TEMP_DEFAULTS;
MODULE_TEMP_CALC  moduleB_TEMP  = MODULE_TEMP_DEFAULTS;
MODULE_TEMP_CALC  moduleC_TEMP  = MODULE_TEMP_DEFAULTS;
TEMPERATURE_CALC  ambient_ntc = NTC_TEMPERATURE_CALC;
TEMPERATURE_CALC  SCR_ntc = NTC_TEMPERATURE_CALC;
TEMPERATURE_CALC  CAP_ntc = NTC_TEMPERATURE_CALC;
TEMPERATURE_CALC  ambient_ntc1 = NTC_TEMPERATURE_CALC;







//--- end of file -----------------------------------------------------
