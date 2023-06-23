/*
 * pid_controller.cpp
 *
 *  Created on: 2023年6月21日
 *      Author: cx
 */

#include <include/pid_controller.hpp>
#include <iostream>
#include <string>


namespace YF
{
	/// \brief Call back (cb) function for communication between PID controller and user.
	void PIDController::cbPidUserInterface(const msgs::PIDControllerTarget &_msgTarget)
	{
	  assert(_msgTarget.pidtarget_size() <= 6);
	  for(int i = 0; i < _msgTarget.pidtarget_size(); i++)
	  {
		  targetPosition[i] = _msgTarget.pidtarget(i);
	  }
	  std::cout << "PID targets = " << targetPosition[0] << "; " << targetPosition[1]
									<< "; " << targetPosition[2] << "; " << targetPosition[3]
									<< "; " << targetPosition[4] << "; " << targetPosition[5]
									<< std::endl;
	}

	PIDController::PIDController()
	{
		// Subscribe to a topic by registering a callback.
		if (!pidUserInterface.Subscribe(pidUserInterfaceTopic, &PIDController::cbPidUserInterface, this))
		{
			std::cerr << "Error subscribe to topic [" << pidUserInterfaceTopic << "]" << std::endl;
			return;
		}
	}

	/// \brief Implement control algorithm here. A control algorithm should fill the joint actuator forces.
    /// This function is called before simulation or real world updates.
    /// Each robot state variable has been processed in parent class JointsController.
    /// Looking up robot state variables in the parent class for details.
    /// [in] Robot state variables: _jointPositions, _jointVelocities
    /// [out] Joint forces: _jointActuatorTorques[i][0] = joint_torque[i], i from 0 to JOINTNUMBER-1
	void PIDController::execControlAlgorithm()
	{
		for (int i = 0; i < _numJoints; i++)
		{
			double force = 0;
			/// Simple PD algorithm
			force = kp[i] * (targetPosition[i] - _jointPositions[i]) + kd[i] * (0 - _jointVelocities[i]);
			SetJointTorque(i, force);
		}
	}
}

