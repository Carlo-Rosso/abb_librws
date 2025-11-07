/***********************************************************************************************************************
 *
 * Copyright (c) 
 * 2015, ABB Schweiz AG
 * 2021, JOiiNT LAB, Fondazione Istituto Italiano di Tecnologia, Intellimech Consorzio per la Meccatronica.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that
 * the following conditions are met:
 *
 *    * Redistributions of source code must retain the
 *      above copyright notice, this list of conditions
 *      and the following disclaimer.
 *    * Redistributions in binary form must reproduce the
 *      above copyright notice, this list of conditions
 *      and the following disclaimer in the documentation
 *      and/or other materials provided with the
 *      distribution.
 *    * Neither the name of ABB nor the names of its
 *      contributors may be used to endorse or promote
 *      products derived from this software without
 *      specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***********************************************************************************************************************
 * 
 * Authors: Gianluca Lentini, Ugo Alberto Simioni
 * Date:18/01/2022
 * Version 1.0
 * Description: this package provides a ROS node that communicates with the controller using Robot Web Services 2.0, original code can be retrieved at https://github.com/ros-industrial/abb_librws
 * 
 ***********************************************************************************************************************
 */

#ifndef RWS_COMMON_H
#define RWS_COMMON_H

#include <iostream>
#include <string>
#include <vector>

#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeList.h"

namespace abb
{
namespace rws
{
/**
 * \brief A struct for representing XML attributes.
 */
struct XMLAttribute
{
  /**
   * \brief A default constructor.
   */
  XMLAttribute() {}
  
  /**
   * \brief A constructor.
   * 
   * \param name for the attribute's name.
   * \param value for the attribute's value.
   */
  XMLAttribute(std::string name, std::string value) : name(name), value(value) {}
  
  /**
   * \brief The name of the attribute.
   */
  std::string name;
  
  /**
   * \brief The value of the attribute.
   */
  std::string value;
};

/**
 * \brief A method for finding all nodes in a XML document that has the specifed attribute (name and value).
 * 
 * \param p_xml_document for the XML document to search.
 * \param attribute specifying the XML attribute (name and value) that the XML node should have.
 *
 * \return std::vector<Poco::XML::Node*> containing the found nodes.
 */
std::vector<Poco::XML::Node*> xmlFindNodes(Poco::AutoPtr<Poco::XML::Document> p_xml_document,
                                           const XMLAttribute attribute);

/**
 * \brief A method for finding the text content of a XML node in a XML document. It stops after the first hit.
 * 
 * \param p_xml_document for the XML document to search.
 * \param attribute specifying the XML attribute (name and value) that the XML text node should have.
 *
 * \return std::string containing the text content. Empty if none were found.
 */
std::string xmlFindTextContent(Poco::AutoPtr<Poco::XML::Document> p_xml_document, const XMLAttribute attribute);

/**
 * \brief A method for finding the text content of a XML node. If not found, then it checks the node's children as well.
 * 
 * \param p_node for the XML node to search.
 * \param attribute specifying the XML attribute (name and value) that the XML text node (child) should have.
 *
 * \return std::string containing the text content. Empty if none were found.
 */
std::string xmlFindTextContent(const Poco::XML::Node* p_node, const XMLAttribute attribute);

/**
 * \brief A method for checking if a XML node has the specified attribute.
 * 
 * \param p_node for the XML node to check.
 * \param attribute specifying the XML attribute (name and value) to check for.
 *
 * \return bool indicating if the attribute was found or not.
 */
bool xmlNodeHasAttribute(const Poco::XML::Node* p_node, const XMLAttribute attribute);

/**
 * \brief Struct containing various constant values defined by default robot controller systems.
 */
struct SystemConstants
{ 
  /**
   * \brief Controller states related constants.
   */
  struct ContollerStates
  {
    /**
     * \brief Robot controller motor on.
     */
    inline static const std::string CONTROLLER_MOTOR_ON       = "motoron";

    /**
     * \brief Robot controller motor off.
     */
    inline static const std::string CONTROLLER_MOTOR_OFF      = "motoroff";

    /**
     * \brief Robot controller auto mode.
     */
    inline static const std::string PANEL_OPERATION_MODE_AUTO = "AUTO";

    /**
     * \brief RAPID running.
     */
    inline static const std::string RAPID_EXECUTION_RUNNING   = "running";
  };
  
  /**
   * \brief General constants.
   */
  struct General
  {
    /**
     * \brief Default name of an application using RWS.
     */
    inline static const std::string EXTERNAL_APPLICATION   = "ExternalApplication";
    
    /**
     * \brief Default location of an application using RWS.
     */
    inline static const std::string EXTERNAL_LOCATION      = "ExternalLocation";

    /**
     * \brief Default port number for RWS communication.
     */
    static constexpr unsigned short DEFAULT_PORT_NUMBER    = 443;
    
    /**
     * \brief Default password (for unconfigured robot controller systems).
     */
    inline static const std::string DEFAULT_PASSWORD       = "robotics";

    /**
     * \brief Default username (for unconfigured robot controller systems).
     */
    inline static const std::string DEFAULT_USERNAME       = "Default User";

    /**
     * \brief Local user.
     */
    inline static const std::string LOCAL                  = "local";

    /**
     * \brief Mechanical unit name for ROB_1.
     */
    inline static const std::string MECHANICAL_UNIT_ROB_1  = "ROB_1";
    
    /**
     * \brief Mechanical unit name for ROB_2.
     */
    inline static const std::string MECHANICAL_UNIT_ROB_2  = "ROB_2";
    
    /**
     * \brief Mechanical unit name for ROB_3.
     */
    inline static const std::string MECHANICAL_UNIT_ROB_3  = "ROB_3";
    
    /**
     * \brief Mechanical unit name for ROB_4.
     */
    inline static const std::string MECHANICAL_UNIT_ROB_4  = "ROB_4";
    
    /**
     * \brief Mechanical unit name for ROB_L.
     */
    inline static const std::string MECHANICAL_UNIT_ROB_L  = "ROB_L";
    
    /**
     * \brief Mechanical unit name for ROB_R.
     */
    inline static const std::string MECHANICAL_UNIT_ROB_R  = "ROB_R";
    
    /**
     * \brief Remote user.
     */
    inline static const std::string REMOTE                 = "remote";
  };

  /**
   * \brief IO signal related constants.
   */
  struct IOSignals
  { 
    /**
     * \brief Name of defined IO signal for smart gripper left position.
     *
     * Note: Requires the Smart Gripper product.
     */
    inline static const std::string HAND_ACTUAL_POSITION_L   = "hand_ActualPosition_L";
        
    /**
     * \brief Name of defined IO signal for smart gripper right position.
     *
     * Note: Requires the Smart Gripper product.
     */
    inline static const std::string HAND_ACTUAL_POSITION_R   = "hand_ActualPosition_R";
        
    /**
     * \brief Name of defined IO signal for smart gripper left speed.
     *
     * Note: Requires the Smart Gripper product.
     */
    inline static const std::string HAND_ACTUAL_SPEED_L      = "hand_ActualSpeed_L";
        
    /**
     * \brief Name of defined IO signal for smart gripper right speed.
     *
     * Note: Requires the Smart Gripper product.
     */
    inline static const std::string HAND_ACTUAL_SPEED_R      = "hand_ActualSpeed_R";
        
    /**
     * \brief Name of defined IO signal for smart gripper left calibration status.
     *
     * Note: Requires the Smart Gripper product.
     */
    inline static const std::string HAND_STATUS_CALIBRATED_L = "hand_StatusCalibrated_L";
        
    /**
     * \brief Name of defined IO signal for smart gripper right calibration status.
     *
     * Note: Requires the Smart Gripper product.
     */
    inline static const std::string HAND_STATUS_CALIBRATED_R = "hand_StatusCalibrated_R";
    
    /**
     * \brief High digital IO signal.
     */
    inline static const std::string HIGH                     = "1";

    /**
     * \brief Low digital IO signal.
     */
    inline static const std::string LOW                      = "0";
  };
    
  /**
   * \brief RAPID related constants.
   */
  struct RAPID
  {
    /**
     * \brief RAPID boolean false.
     */
    inline static const std::string RAPID_FALSE = "FALSE";

    /**
     * \brief RAPID boolean true.
     */
    inline static const std::string RAPID_TRUE  = "TRUE";
    
    /**
     * \brief Default name for the first robot RAPID motion task.
     */
    inline static const std::string TASK_ROB_1  = "T_ROB1";

    /**
     * \brief Default name for the second robot RAPID motion task.
     */
    inline static const std::string TASK_ROB_2  = "T_ROB2";

    /**
     * \brief Default name for the third robot RAPID motion task.
     */
    inline static const std::string TASK_ROB_3  = "T_ROB3";

    /**
     * \brief Default name for the fourth robot RAPID motion task.
     */
    inline static const std::string TASK_ROB_4  = "T_ROB4";

    /**
     * \brief Default name for the IRB14000 (a.k.a YuMi) left arm robot RAPID motion task.
     */
    inline static const std::string TASK_ROB_L  = "T_ROB_L";
        
    /**
     * \brief Default name for the IRB14000 (a.k.a YuMi) right arm robot RAPID motion task.
     */
    inline static const std::string TASK_ROB_R  = "T_ROB_R";
    
    /**
     * \brief RAPID data type bool.
     */
    inline static const std::string TYPE_BOOL   = "bool";
    
    /**
     * \brief RAPID data type dnum.
     */
    inline static const std::string TYPE_DNUM   = "dnum";
    
    /**
     * \brief RAPID data type num.
     */
    inline static const std::string TYPE_NUM    = "num";
    
    /**
     * \brief RAPID data type string.
     */
    inline static const std::string TYPE_STRING = "string";
  };

  /**
   * \brief Robot Web Services (RWS) related constants.
   */
  struct RWS
  {
    /**
     * \brief XML attributes specifying names with corresponding values.
     */
    struct XMLAttributes
    {
      /**
       * \brief Class & cfg-ia-t-li.
       */
  inline static const XMLAttribute CLASS_CFG_IA_T_LI = XMLAttribute("class", "cfg-ia-t-li");

      /**
       * \brief Class & controller execution state.
       */
  inline static const XMLAttribute CLASS_CTRLEXECSTATE = XMLAttribute("class", "ctrlexecstate");

      /**
       * \brief Class & controller state.
       */
  inline static const XMLAttribute CLASS_CTRLSTATE = XMLAttribute("class", "ctrlstate");
      
      /**
       * \brief Class & data type.
       */
  inline static const XMLAttribute CLASS_DATTYP = XMLAttribute("class", "dattyp");
      
      /**
       * \brief Class & ios-signal.
       */
  inline static const XMLAttribute CLASS_IOS_SIGNAL = XMLAttribute("class", "ios-signal");

      /**
       * \brief Class & lvalue.
       */
  inline static const XMLAttribute CLASS_LVALUE = XMLAttribute("class", "lvalue");
      
      /**
       * \brief Class & motiontask.
       */
  inline static const XMLAttribute CLASS_MOTIONTASK = XMLAttribute("class", "motiontask");
      
      /**
       * \brief Class & name.
       */
  inline static const XMLAttribute CLASS_NAME = XMLAttribute("class", "name");

      /**
       * \brief Class & operation mode.
       */
  inline static const XMLAttribute CLASS_OPMODE = XMLAttribute("class", "opmode");
      
      /**
       * \brief Class & rap-module-info-li.
       */
  inline static const XMLAttribute CLASS_RAP_MODULE_INFO_LI = XMLAttribute("class", "rap-module-info-li");

      /**
       * \brief Class & rap-task-li.
       */
  inline static const XMLAttribute CLASS_RAP_TASK_LI = XMLAttribute("class", "rap-task-li");

      /**
       * \brief Class & RobotWare version name.
       */
  inline static const XMLAttribute CLASS_RW_VERSION_NAME = XMLAttribute("class", "rwversionname");

      /**
       * \brief Class & state.
       */
  inline static const XMLAttribute CLASS_STATE = XMLAttribute("class", "state");
      
      /**
       * \brief Class & sys-system-li.
       */
  inline static const XMLAttribute CLASS_SYS_SYSTEM_LI = XMLAttribute("class", "sys-system-li");

      /**
       * \brief Class & type.
       */
  inline static const XMLAttribute CLASS_TYPE = XMLAttribute("class", "type");

      /**
       * \brief Class & value.
       */
      inline static const XMLAttribute CLASS_VALUE = XMLAttribute("class", "value");
    };
    
    /**
     * \brief Identifiers in different RWS messages. E.g. XML attribute names/values.
     */
    struct Identifiers
    {
      /**
       * \brief XML attribute name: class.
       */
  inline static const std::string CLASS                          = "class";

      /**
       * \brief Configuration list item.
       */
  inline static const std::string CFG_IA_T_LI                    = "cfg-ia-t-li";

      /**
       * \brief Controller execution state.
       */
  inline static const std::string CTRLEXECSTATE                  = "ctrlexecstate";
      
      /**
       * \brief Controller state.
       */
  inline static const std::string CTRLSTATE                      = "ctrlstate";
      
      /**
       * \brief Data type.
       */
  inline static const std::string DATTYP                         = "dattyp";

      /**
       * \brief Home directory.
       */
  inline static const std::string HOME_DIRECTORY                 = "$home";
      
      /**
       * \brief IO signal.
       */
  inline static const std::string IOS_SIGNAL                     = "ios-signal";

      /**
       * \brief Motion task.
       */
  inline static const std::string MOTIONTASK                     = "motiontask";
      
      /**
       * \brief Name.
       */
  inline static const std::string NAME                           = "name";
      
      /**
       * \brief Lvalue.
       */
  inline static const std::string LVALUE                         = "lvalue";

      /**
       * \brief Opmode.
       */
  inline static const std::string OPMODE                         = "opmode";

      /**
       * \brief Options present on the controller.
       */
  inline static const std::string PRESENT_OPTIONS                = "present_options";

      /**
       * \brief RAPID module info list item.
       */
  inline static const std::string RAP_MODULE_INFO_LI             = "rap-module-info-li";

      /**
       * \brief RAPID task list item.
       */
  inline static const std::string RAP_TASK_LI                    = "rap-task-li";
      
      /**
       * \brief RobotWare version name.
       */
  inline static const std::string RW_VERSION_NAME                = "rwversionname";
      
      /**
       * \brief State.
       */
  inline static const std::string STATE                          = "state";

      /**
       * \brief Controller topic in the system configurations (abbreviated as sys).
       */
  inline static const std::string SYS                            = "sys";
      
      /**
       * \brief Sys system list item.
       */
  inline static const std::string SYS_SYSTEM_LI                  = "sys-system-li";

      /**
       * \brief Type.
       */
  inline static const std::string TYPE                           = "type";

      /**
       * \brief Value.
       */
      inline static const std::string VALUE                          = "value";
    };

    /**
     * \brief RWS queries.
     */

     /**
     * \brief RWS services.
     */
    struct Services
    {
      /**
       * \brief Controller service.
       */
      inline static const std::string CTRL      = "/ctrl";

      /**
       * \brief Fileservice.
       */
      inline static const std::string FILESERVICE = "/fileservice";

      /**
       * \brief RobotWare service.
       */
      inline static const std::string RW         = "/rw";

      /**
       * \brief Subscription service.
       */
      inline static const std::string SUBSCRIPTION = "/subscription";

      /**
       * \brief User service.
       */
      inline static const std::string USERS      = "/users";
    };
    struct Queries
    {
      /**
       * \brief Release action query.
       */
      inline static const std::string ACTION_RELEASE = "release";
      
      /**
       * \brief Request action query.
       */
      inline static const std::string ACTION_REQUEST = "request";
      
      /**
       * \brief Reset program pointer action query.
       */
      inline static const std::string ACTION_RESETPP = "resetpp";

      /**
       * \brief Set action query.
       */
      inline static const std::string ACTION_SET = "set-value";
      
      /**
       * \brief Set controller state action query.
       */
      inline static const std::string ACTION_SETCTRLSTATE = "action=setctrlstate";

      /**
       * \brief Set locale.
       */
      inline static const std::string ACTION_SET_LOCALE = "action=set-locale";

      /**
       * \brief Start action query.
       */
      inline static const std::string ACTION_START = "start";
      
      /**
       * \brief Stop action query.
       */
      inline static const std::string ACTION_STOP = "stop";

      /**
       * \brief Task query.
       */
      inline static const std::string TASK = "task=";
    };

    /**
     * \brief RWS resources and queries.
     */
    struct Resources
    {
      /**
       * \brief Instances.
       */
      inline static const std::string INSTANCES                        = "/instances";

      /**
       * \brief Jointtarget.
       */
      inline static const std::string JOINTTARGET                      = "/jointtarget";
      
      /**
       * \brief Logout.
       */
      inline static const std::string LOGOUT                           = "/logout";

      /**
       * \brief Robtarget.
       */
      inline static const std::string ROBTARGET                        = "/robtarget";

      /**
       * \brief Lead Through.
       */
      inline static const std::string LEADTHROUGH                      = "/lead-through";

      /**
       * \brief Modules.
       */
      inline static const std::string MODULES                          = "/modules";

      /**
       * \brief Configurations.
       */
      inline static const std::string RW_CFG                           = Services::RW + "/cfg";

      /**
       * \brief Signals.
       */
      inline static const std::string RW_IOSYSTEM_SIGNALS              = Services::RW + "/iosystem/signals";

      /**
       * \brief Mastership.
       */
      inline static const std::string RW_MASTERSHIP                    = Services::RW + "/mastership/edit";
      
      /**
       * \brief Mechanical units.
       */
      inline static const std::string RW_MOTIONSYSTEM_MECHUNITS        = Services::RW + "/motionsystem/mechunits";

      /**
       * \brief Panel controller state.
       */
      inline static const std::string RW_PANEL_CTRLSTATE               = Services::RW + "/panel/ctrl-state";

      /**
       * \brief Panel operation mode.
       */
      inline static const std::string RW_PANEL_OPMODE                  = Services::RW + "/panel/opmode";

      /**
       * \brief RAPID execution.
       */
      inline static const std::string RW_RAPID_EXECUTION               = Services::RW + "/rapid/execution";

      /**
       * \brief RAPID modules.
       */
      inline static const std::string RW_RAPID_MODULES                 = Services::RW + "/rapid/modules";

      /**
       * \brief RAPID symbol data.
       */
      inline static const std::string RW_RAPID_SYMBOL_DATA_RAPID       = Services::RW + "/rapid/symbol/RAPID";
      
      /**
       * \brief RAPID symbol properties.
       */
      inline static const std::string RW_RAPID_SYMBOL_PROPERTIES_RAPID = Services::RW + "/rapid/symbol/RAPID";

      /**
       * \brief RAPID tasks.
       */
      inline static const std::string RW_RAPID_TASKS                   = Services::RW + "/rapid/tasks";

      /**
       * \brief RobotWare system.
       */
      inline static const std::string RW_SYSTEM                        = Services::RW + "/system";
    };
  };
};

/**
 * \brief A class for a three-valued boolean.
 */
class TriBool
{
public:
  /**
   * \brief An enum for the different accepted values.
   */
  enum Values
  {
    UNKNOWN_VALUE, ///< Unknown value. E.g. in case of communication failure.
    TRUE_VALUE,    ///< True value.
    FALSE_VALUE    ///< False value.
  };

  /**
   * \brief A default constructor.
   */
  TriBool() : value(UNKNOWN_VALUE) {}

  /**
   * \brief A constructor.
   */
  TriBool(const Values initial_value) : value(initial_value) {}

  /**
   * \brief A constructor.
   *
   * \param value for the initial true or false value.
   */
  TriBool(const bool initial_value) : value(initial_value ? TRUE_VALUE : FALSE_VALUE) {}

  /**
   * \brief Operator for copy assignment.
   *
   * \param rhs for right hand side value.
   *
   * \return TriBool& self.
   */
  TriBool& operator=(const TriBool& other)
  {
    if (&other == this)
    {
      return *this;
    }

    value = other.value;

    return *this;
  }

  /**
   * \brief Operator for assignment.
   *
   * \param rhs for right hand side value.
   *
   * \return TriBool& self.
   */
  TriBool& operator=(const Values& rhs)
  {
    value = rhs;

    return *this;
  }

  /**
   * \brief Operator for assignment.
   *
   * \param rhs for right hand side value.
   *
   * \return TriBool& self.
   */
  TriBool& operator=(const bool& rhs)
  {
    value = (rhs ? TRUE_VALUE : FALSE_VALUE);

    return *this;
  }

  /**
   * \brief Operator for equal to comparison.
   *
   * \param rhs for right hand side value.
   *
   * \return bool indicating if the comparision was equal or not.
   */
  bool operator==(const TriBool& rhs) const
  {
    return value == rhs.value;
  }

  /**
   * \brief Operator for equal to comparison.
   *
   * \param rhs for right hand side value.
   *
   * \return bool indicating if the comparision was equal or not.
   */
  bool operator==(const Values& rhs) const
  {
    return value == rhs;
  }

  /**
   * \brief Operator for not equal to comparison.
   *
   * \param rhs for right hand side value.
   *
   * \return bool indicating if the comparision was not equal or not.
   */
  bool operator!=(const TriBool& rhs) const
  {
    return value != rhs.value;
  }

  /**
   * \brief Operator for not equal to comparison.
   *
   * \param rhs for right hand side value.
   *
   * \return bool indicating if the comparision was not equal or not.
   */
  bool operator!=(const Values& rhs) const
  {
    return value != rhs;
  }

  /**
   * \brief Operator for stream insertion.
   *
   * \param stream for the output stream.
   * \param rhs for the right hand side value, to insert into the output stream.
   *
   * \return std::ostream& for the output stream.
   */
  friend std::ostream& operator<<(std::ostream& stream, const TriBool& rhs)
  {
    return stream << rhs.toString();
  }

  /**
   * \brief A method for checking if the tri bool is unknown.
   *
   * \return bool indicating if the tri bool is unknown or not.
   */
  bool isUnknown() const
  {
    return value == UNKNOWN_VALUE;
  }

  /**
   * \brief A method for checking if the tri bool is true.
   *
   * \return bool indicating if the tri bool is true or not.
   */
  bool isTrue() const
  {
    return value == TRUE_VALUE;
  }

  /**
   * \brief A method for checking if the tri bool is false.
   *
   * \return bool indicating if the tri bool is false or not.
   */
  bool isFalse() const
  {
    return value == FALSE_VALUE;
  }

  /**
   * \brief A method for converting the tri bool to a text string.
   *
   * \return std::string containing the string representation of the value.
   */
  std::string toString() const
  {
    return (isUnknown() ? "unknown" : (isTrue() ? "true" : "false"));
  }

private:
  /**
   * \brief The tri bool value.
   */
  Values value;
};

} // end namespace rws
} // end namespace abb

#endif
