/*
 * Copyright (C) 2013 CoDyCo
 * Author: Daniele Pucci
 * email:  daniele.pucci@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

#ifndef JOINT_TORQUE_CONTROL_PARAMS
#define JOINT_TORQUE_CONTROL_PARAMS

#include <paramHelp/paramProxyBasic.h>
#include <Eigen/Core>                               // import most common Eigen types
#include <vector>
#include <string>

using namespace paramHelp;
using namespace Eigen;
using namespace std;

namespace jointTorqueControl
{
    
    static const int N_DOF = 25;
    typedef Eigen::Array<double,N_DOF,1>            VectorNd;
    typedef Eigen::Matrix<double,N_DOF+6,1>         VectorNp6d;
    typedef Eigen::Array<int,N_DOF,1>               VectorNi;
    
    static const int SEND_COMMANDS_ACTIVE = 1;
    static const int SEND_COMMANDS_NONACTIVE = 0;
    
    // *** DEFAULT PARAMETER VALUES
    static const string		DEFAULT_MODULE_NAME     = "jtc";
    static const string		DEFAULT_ROBOT_NAME      = "icubSim";                // robot name
    static const int        DEFAULT_CTRL_PERIOD     = 10;                       // controller period in ms
    static const int        DEFAULT_SENDCMD     	= SEND_COMMANDS_ACTIVE;     //
    static const int        DEFAULT_GRAV_COMP_ON    = 1;                        // 1=gravity compensation on, 0=off
    static const VectorNi	DEFAULT_ACTIVE_JOINTS   = VectorNi::Constant(0);
    
    static const VectorNd	DEFAULT_KT				= VectorNd::Constant(0.0);
    static const VectorNd	DEFAULT_KVP				= VectorNd::Constant(0.0);
    static const VectorNd	DEFAULT_KVN				= VectorNd::Constant(0.0);
    static const VectorNd	DEFAULT_KCP				= VectorNd::Constant(0.0);
    static const VectorNd	DEFAULT_KCN				= VectorNd::Constant(0.0);
    static const VectorNd	DEFAULT_ZEROS_NDOF  	= VectorNd::Constant(0.0);
    
    static const VectorNd	DEFAULT_KP				    = VectorNd::Constant(0.0);
    static const VectorNd   DEFAULT_KI                  = VectorNd::Constant(0.0);
    static const VectorNd   DEFAULT_KD                  = VectorNd::Constant(0.0);
    static const VectorNd	DEFAULT_COULOMB_VEL_THR	    = VectorNd::Constant(5.0);
    
    static const VectorNd	DEFAULT_TAUD			= VectorNd::Constant(0.0);
    
    static const VectorNd   DEFAULT_FRICTION_COMPENSATION = VectorNd::Zero();
    static const double     DEFAULT_TORQUE_FILT_CUT_FREQ = 1.0;
    
    static const VectorNd	DEFAULT_VMAX			= VectorNd::Constant(100.0);
    static const double		KT_MAX 		         	= 100.0;
    static const double		KVP_MAX     	     	= 100.0;
    static const double		KVN_MAX         	 	= 100.0;
    static const double		KCP_MAX          		= 100.0;
    static const double		KCN_MAX	        	  	= 100.0;
    static const double		KI_MAX  	        	= 100.0;
    static const double		KP_MAX      	    	= 100.0;
    static const double		KS_MAX          		= 100.0;
    static const double		V_MAX 	       		  	= 100.0;
    static const double		TAUD_MIN          		= -10.0;
    static const double		TAUD_MAX 	        	= 10.0;
    static const double		VM_MIN          		= -1333.0;
    static const double		VM_MAX	 	        	= 1333.0;
    
    
    
    // *** IDs of all the module parameters
    enum jointTorqueControlParamId {
        PARAM_ID_MODULE_NAME,	PARAM_ID_CTRL_PERIOD,	    PARAM_ID_ROBOT_NAME,
        /* RPC PARAMETERS */
        PARAM_ID_AJ,	        PARAM_ID_KT,	            PARAM_ID_KVP,
        PARAM_ID_KVN,	        PARAM_ID_KCP,	            PARAM_ID_KCN,
        PARAM_ID_KP,	        PARAM_ID_KI,                PARAM_ID_KD,	            PARAM_ID_COULOMB_VEL_THR,
        PARAM_ID_VMAX,	        PARAM_ID_SENDCMD,           PARAM_ID_MONITORED_JOINT,
        PARAM_ID_KSTIFF,        PARAM_ID_KDAMP,                PARAM_ID_GRAV_COMP_ON,
        PARAM_ID_Q_DES,         PARAM_ID_FRICTION_COMPENSATION,
        PARAM_ID_TORQUE_FILT_CUT_FREQ,
        /* STREAMING INPUT PARAMETERS */
        PARAM_ID_TAU_OFFSET,    PARAM_ID_TAU_SIN_AMPL,      PARAM_ID_TAU_SIN_FREQ,
        PARAM_ID_Q_SIN_AMPL,    PARAM_ID_Q_SIN_FREQ,
        /* STREAMING OUTPUT PARAMETERS */
        PARAM_ID_VM,	        PARAM_ID_TAU,
        /* MONITOR PARAMETERS*/
        PARAM_ID_TAU_MEAS,      PARAM_ID_TAUD_MONITOR,
        PARAM_ID_TAU_MEAS1,     PARAM_ID_TAUD_MONITOR1,
        PARAM_ID_TAU_MEAS2,     PARAM_ID_TAUD_MONITOR2,
        PARAM_ID_TAUD_PLUS_PI,  PARAM_ID_TAU_ERR,
        PARAM_ID_Q,             PARAM_ID_Q_DES_MONITOR,
        PARAM_ID_JOINT_VEL,     PARAM_ID_JOINT_VEL_SIGN,
        PARAM_ID_PWM_DESIRED,   PARAM_ID_PWM_FEEDFORWARD,   PARAM_ID_PWM_FEEDBACK,
        PARAM_ID_PWM_TORQUE_FF, PARAM_ID_PWM_FRICTION_FF,   PARAM_ID_PWM_MEASURED,
        PARAM_ID_SIZE,
    };
    
    
    // ******************************************************************************************************************************
    // ****************************************** DESCRIPTION OF ALL THE MODULE PARAMETERS ******************************************
    // ******************************************************************************************************************************
    const ParamProxyInterface *const jointTorqueControlParamDescr[PARAM_ID_SIZE]  =
    {
        //	              	        NAME                    ID                              SIZE   		BOUNDS          		                        I/O ACCESS          DEFAULT VALUE                   DESCRIPTION
        new ParamProxyBasic<string>("name",           	    PARAM_ID_MODULE_NAME,           1,			                                                PARAM_CONFIG,       &DEFAULT_MODULE_NAME,           "Name of the instance of the module"),
        new ParamProxyBasic<int>(   "period",         	    PARAM_ID_CTRL_PERIOD,           1,			ParamBilatBounds<int>(1, 1000),                 PARAM_CONFIG,       &DEFAULT_CTRL_PERIOD,           "Period of the control loop (ms)"),
        new ParamProxyBasic<string>("robot",			    PARAM_ID_ROBOT_NAME,            1,			                                                PARAM_CONFIG,       &DEFAULT_ROBOT_NAME,            "Name of the robot"),
        // ************************************************ RPC PARAMETERS ****************************************************************************************************************************************************************************************************************************************
        new ParamProxyBasic<int>(   "activeJoints",		    PARAM_ID_AJ,                    N_DOF,		ParamBilatBounds<int>(0, 1),			        PARAM_IN_OUT,       DEFAULT_ACTIVE_JOINTS.data(),	"Vector of nDOF integers representing the joints to control  (1: active, 0: inactive)"),
        new ParamProxyBasic<double>("kt",          	        PARAM_ID_KT,                    N_DOF,		ParamBilatBounds<double>(0.0, KT_MAX),		    PARAM_IN_OUT,       DEFAULT_KT.data(),				"Vector of nDOF floats ( see Eq. (1) )"),
        new ParamProxyBasic<double>("kvp",          	    PARAM_ID_KVP,                   N_DOF,		ParamBilatBounds<double>(0.0, KVP_MAX),		    PARAM_IN_OUT,       DEFAULT_KVP.data(),				"Vector of nDOF floats ( see Eq. (2) )"),
        new ParamProxyBasic<double>("kvn",          	    PARAM_ID_KVN,                   N_DOF,		ParamBilatBounds<double>(0.0, KVN_MAX),		    PARAM_IN_OUT,       DEFAULT_KVN.data(),				"Vector of nDOF floats ( see Eq. (2) )"),
        new ParamProxyBasic<double>("kcp",		            PARAM_ID_KCP,                   N_DOF,		ParamBilatBounds<double>(0.0, KCP_MAX),		    PARAM_IN_OUT,       DEFAULT_KCP.data(),				"Vector of nDOF floats ( see Eq. (2) )"),
        new ParamProxyBasic<double>("kcn",     	            PARAM_ID_KCN,                   N_DOF,		ParamBilatBounds<double>(0.0, KCN_MAX),		    PARAM_IN_OUT,       DEFAULT_KCN.data(),				"Vector of nDOF floats ( see Eq. (2) )"),
        new ParamProxyBasic<double>("kp",          	        PARAM_ID_KP,                    N_DOF,		ParamBilatBounds<double>(0.0, KP_MAX),		    PARAM_IN_OUT,       DEFAULT_KP.data(),				"Vector of nDOF floats representing the position gains ( see Eq. (x) )"),
        new ParamProxyBasic<double>("ki",                   PARAM_ID_KI,                    N_DOF,      ParamBilatBounds<double>(0.0, KI_MAX),          PARAM_IN_OUT,       DEFAULT_KI.data(),              "Vector of nDOF floats representing the integral gains ( see Eq. (x) )"),
        new ParamProxyBasic<double>("kd",                   PARAM_ID_KD,                    N_DOF,      ParamBilatBounds<double>(0.0, KI_MAX),          PARAM_IN_OUT,       DEFAULT_KD.data(),              "Vector of nDOF floats representing the derivative gains ( see Eq. (x) )"),
        new ParamProxyBasic<double>("coulomb vel thr",      PARAM_ID_COULOMB_VEL_THR,       N_DOF,		ParamBilatBounds<double>(0.0, 10.0),		    PARAM_IN_OUT,       DEFAULT_COULOMB_VEL_THR.data(),	"Vector of nDOF floats representing the joint vel (deg/s) at which Coulomb friction is completely compensated"),
        new ParamProxyBasic<double>("Vmax",          	    PARAM_ID_VMAX,                  N_DOF,		ParamBilatBounds<double>(0.0, V_MAX),		    PARAM_IN_OUT,       DEFAULT_VMAX.data(),			"Vector of nDOF positive floats representing the tensions' bounds (|Vm| < Vmax"),
        new ParamProxyBasic<int>(   "sendCommands",   	 	PARAM_ID_SENDCMD,               1,			ParamBilatBounds<int>(0, 1),				    PARAM_IN_OUT,       &DEFAULT_SENDCMD,				"If equal to 1, send commands for torque control"),
        new ParamProxyBasic<string>("monitored joint",     	PARAM_ID_MONITORED_JOINT,       1,							                                PARAM_IN_OUT,       0,		                        "Name of the joint to monitor"),
        new ParamProxyBasic<double>("kStiff",          	    PARAM_ID_KSTIFF,                    N_DOF,		ParamBilatBounds<double>(0.0, 100.0),		    PARAM_IN_OUT,   DEFAULT_ZEROS_NDOF.data(),		"Joint stiffnesses"),
        new ParamProxyBasic<double>("kDamp",          	    PARAM_ID_KDAMP,                    N_DOF,		ParamBilatBounds<double>(0.0, 100.0),		    PARAM_IN_OUT,   DEFAULT_ZEROS_NDOF.data(),		"Joint dampings"),
        new ParamProxyBasic<int>(   "grav comp on",         PARAM_ID_GRAV_COMP_ON,          1,		    ParamBilatBounds<int>(0, 1),		            PARAM_IN_OUT,       &DEFAULT_GRAV_COMP_ON,		    "1 if gravity compensation is on, 0 otherwise"),
        new ParamProxyBasic<double>("qDes",          	    PARAM_ID_Q_DES,                 N_DOF,		ParamBilatBounds<double>(-180.0, 180.0),		PARAM_IN_OUT,       DEFAULT_ZEROS_NDOF.data(),		"Desired joint angles"),
        new ParamProxyBasic<double>("fcomp",          	    PARAM_ID_FRICTION_COMPENSATION, N_DOF,		ParamBilatBounds<double>(0, 1.0),               PARAM_IN_OUT,       DEFAULT_FRICTION_COMPENSATION.data(), "Viscous friction compensation factor (from 0.0 to 1.0)"),
        new ParamProxyBasic<double>("tau cut freq",    	    PARAM_ID_TORQUE_FILT_CUT_FREQ,  1,          ParamBilatBounds<double>(0, 10.0),              PARAM_IN_OUT,       &DEFAULT_TORQUE_FILT_CUT_FREQ,  "Cut frequency of torque low-pass filter (in [0 10])"),
        // ************************************************* STREAMING INPUT PARAMETERS ****************************************************************************************************************************************************************************************************************************
        new ParamProxyBasic<double>("tauOffset",        	PARAM_ID_TAU_OFFSET,            N_DOF,      ParamBilatBounds<double>(TAUD_MIN, TAUD_MAX),   PARAM_IN_STREAM,    DEFAULT_TAUD.data(),			"Constant offset added to the desired joint torques"),
        new ParamProxyBasic<double>("tauSinAmpl",        	PARAM_ID_TAU_SIN_AMPL,          N_DOF,      ParamBilatBounds<double>(0.0, TAUD_MAX),        PARAM_IN_STREAM,    DEFAULT_ZEROS_NDOF.data(),		"Amplitudes of the sinusoidal signals that are added to the desired joint torques"),
        new ParamProxyBasic<double>("tauSinFreq",        	PARAM_ID_TAU_SIN_FREQ,          N_DOF,      ParamBilatBounds<double>(0.0, 10.0),            PARAM_IN_STREAM,    DEFAULT_ZEROS_NDOF.data(),		"Frequencies of the sinusoidal signals that are added to the desired joint torques"),
        new ParamProxyBasic<double>("qSinAmpl",             PARAM_ID_Q_SIN_AMPL,            N_DOF,      ParamBilatBounds<double>(0.0, 1.0),             PARAM_IN_STREAM,    DEFAULT_ZEROS_NDOF.data(),		"Amplitudes of the sinusoidal signals used as desired joint positions in inv dyn"),
        new ParamProxyBasic<double>("qSinFreq",             PARAM_ID_Q_SIN_FREQ,            N_DOF,      ParamBilatBounds<double>(0.0, 3.0),             PARAM_IN_STREAM,    DEFAULT_ZEROS_NDOF.data(),		"Frequencies of the sinusoidal signals used as desired joint positions in inv dyn"),
        // ************************************************* STREAMING OUTPUT PARAMETERS ****************************************************************************************************************************************************************************************************************************
        new ParamProxyBasic<double>("Vm",				    PARAM_ID_VM,                    N_DOF,		ParamBilatBounds<double>(VM_MIN, VM_MAX),		PARAM_OUT_STREAM,   0,				                "Vector of nDOF floats representing the motor PWM"),
        new ParamProxyBasic<double>("tau",          	    PARAM_ID_TAU,                   N_DOF,      ParamBilatBounds<double>(TAUD_MIN, TAUD_MAX),	PARAM_OUT_STREAM,   0,        		                "Estimated joint torques"),
        // ************************************************* MONITOR  PARAMETERS ****************************************************************************************************************************************************************************************************************************
        new ParamProxyBasic<double>("tauMeas",              PARAM_ID_TAU_MEAS,          1,                                                          PARAM_MONITOR,      0,                              "Torque of the monitored motor"),
        new ParamProxyBasic<double>("tauDes",               PARAM_ID_TAUD_MONITOR,      1,                                                          PARAM_MONITOR,      0,                              "Desired torque of the monitored motor"),
        new ParamProxyBasic<double>("tauMeas1",             PARAM_ID_TAU_MEAS1,         1,                                                          PARAM_MONITOR,      0,                              "Torque of the monitored motor"),
        new ParamProxyBasic<double>("tauDes1",              PARAM_ID_TAUD_MONITOR1,     1,                                                          PARAM_MONITOR,      0,                              "Desired torque of the monitored motor"),
        new ParamProxyBasic<double>("tauMeas2",             PARAM_ID_TAU_MEAS2,         1,                                                          PARAM_MONITOR,      0,                              "Torque of the monitored motor"),
        new ParamProxyBasic<double>("tauDes2",              PARAM_ID_TAUD_MONITOR2,     1,                                                          PARAM_MONITOR,      0,                              "Desired torque of the monitored motor"),
        new ParamProxyBasic<double>("tauDesPlusPI",         PARAM_ID_TAUD_PLUS_PI,      1,                                                          PARAM_MONITOR,      0,                              "Desired torque plus proportional and integral terms of the monitored motor"),
        new ParamProxyBasic<double>("tauErr",               PARAM_ID_TAU_ERR,           1,                                                          PARAM_MONITOR,      0,                              "Tracking torque error"),
        new ParamProxyBasic<double>("dq",                   PARAM_ID_JOINT_VEL,         1,                                                          PARAM_MONITOR,      0,                              "Velocity of the monitored motor"),
        new ParamProxyBasic<double>("sign dq",              PARAM_ID_JOINT_VEL_SIGN,    1,                                                          PARAM_MONITOR,      0,                              "Sign of the velocity of the monitored motor"),
        new ParamProxyBasic<double>("pwmDes",               PARAM_ID_PWM_DESIRED,       1,                                                          PARAM_MONITOR,      0,                              "PWM commanded to the monitored motor"),
        new ParamProxyBasic<double>("pwmFF",                PARAM_ID_PWM_FEEDFORWARD,   1,                                                          PARAM_MONITOR,      0,                              "Feedforward part of the PWM commanded to the monitored motor"),
        new ParamProxyBasic<double>("pwmFB",                PARAM_ID_PWM_FEEDBACK,      1,                                                          PARAM_MONITOR,      0,                              "Feedback part of the PWM commanded to the monitored motor"),
        new ParamProxyBasic<double>("pwmTorqueFF",          PARAM_ID_PWM_TORQUE_FF,     1,                                                          PARAM_MONITOR,      0,                              "Torque feedforward term of the PWM commanded to the monitored motor"),
        new ParamProxyBasic<double>("pwmFrictionFF",        PARAM_ID_PWM_FRICTION_FF,   1,                                                          PARAM_MONITOR,      0,                              "Friction feedforward term of the PWM commanded to the monitored motor"),
        new ParamProxyBasic<double>("pwmMeas",              PARAM_ID_PWM_MEASURED,      1,                                                          PARAM_MONITOR,      0,                              "Measured PWM of the monitored motor"),
        new ParamProxyBasic<double>("q",                    PARAM_ID_Q,                 1,                                                          PARAM_MONITOR,      0,                              "Joint angle"),
        new ParamProxyBasic<double>("qd",                   PARAM_ID_Q_DES_MONITOR,     1,                                                          PARAM_MONITOR,      0,                              "Desired joint angle")
    };
    
    // *** IDs of all the module command
    enum jointTorqueControlCommandId {
        COMMAND_ID_START,   COMMAND_ID_STOP,    COMMAND_ID_HELP,    COMMAND_ID_QUIT,
        COMMAND_ID_SIZE
    };
    // ******************************************************************************************************************************
    // ****************************************** DESCRIPTION OF ALL THE MODULE COMMANDS ********************************************
    // ******************************************************************************************************************************
    const CommandDescription jointTorqueControlCommandDescr[]  = 
    { 
        //  	                NAME            ID                          DESCRIPTION
        CommandDescription("start",         COMMAND_ID_START,           "Start the control actions"), 
        CommandDescription("stop",          COMMAND_ID_STOP,            "Stop the control actions"), 
        CommandDescription("help",          COMMAND_ID_HELP,            "Get instructions about how to communicate with this module"), 
        CommandDescription("quit",          COMMAND_ID_QUIT,            "Stop the control actions and quit the module"), 
    };
    
}

#endif
