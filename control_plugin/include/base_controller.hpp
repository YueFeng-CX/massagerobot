/*
 * base_controller.cpp
 *
 *  Created on: 2023年6月20日
 *      Author: cx
 */

#ifndef BASECONTROLLER_HPP_
#define BASECONTROLLER_HPP_

#include <gz/sim.hh>
namespace YF
{

	/// BaseController class is the base class for controllers.
	/// It specifies the basic interface definitions for a controller.
	class BaseController
	{
	  protected:
		  BaseController();

	  public:
		  virtual ~BaseController() = 0;
		  virtual void PreUpdate(const gz::sim::UpdateInfo &_info,
				  gz::sim::EntityComponentManager &_ecm) = 0;
		  virtual void PostUpdate(const gz::sim::UpdateInfo &_info,
				  const gz::sim::EntityComponentManager &_ecm) = 0;
	};

}
#endif /* BASECONTROLLER_HPP_ */
