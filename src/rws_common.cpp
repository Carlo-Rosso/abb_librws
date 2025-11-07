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

#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeList.h"

#include "abb_librws/rws_common.h"

namespace abb
{
namespace rws
{
/***********************************************************************************************************************
 * Function definitions
 */

std::vector<Poco::XML::Node*> xmlFindNodes(Poco::AutoPtr<Poco::XML::Document> p_xml_document,
                                           const XMLAttribute attribute)
{
  std::vector<Poco::XML::Node*> result;

  if (!p_xml_document.isNull())
  {
    Poco::XML::NodeIterator node_iterator(p_xml_document, Poco::XML::NodeFilter::SHOW_ELEMENT);
    Poco::XML::Node* p_node = node_iterator.nextNode();

    while (p_node)
    {
      if (xmlNodeHasAttribute(p_node, attribute))
      {
        result.push_back(p_node);
      }

      p_node = node_iterator.nextNode();
    }
  }

  return result;
}

std::string xmlFindTextContent(Poco::AutoPtr<Poco::XML::Document> p_xml_document, const XMLAttribute attribute)
{
  std::string result;

  if (!p_xml_document.isNull())
  {
    Poco::XML::NodeIterator node_iterator(p_xml_document, Poco::XML::NodeFilter::SHOW_ELEMENT);
    result = xmlFindTextContent(node_iterator.nextNode(), attribute);
  }

  return result;
}

std::string xmlFindTextContent(const Poco::XML::Node* p_node, const XMLAttribute attribute)
{
  std::string result;

  if (p_node)
  {
    if (p_node->nodeType() == Poco::XML::Node::TEXT_NODE && xmlNodeHasAttribute(p_node->parentNode(), attribute))
    {
      result = p_node->nodeValue();
    }
    else
    {
      bool found = false;
      if (p_node->hasChildNodes())
      {
        Poco::AutoPtr<Poco::XML::NodeList> p_children(p_node->childNodes());

        for (unsigned long i = 0; i < p_children->length() && !found; i++)
        {
          Poco::XML::Node* p_child = p_children->item(i);

          if (p_child->nodeType() == Poco::XML::Node::TEXT_NODE && xmlNodeHasAttribute(p_child->parentNode(), attribute))
          {
            found = true;
            result = p_child->nodeValue();
          }
          else
          {
            result = xmlFindTextContent(p_child, attribute);
            found = !result.empty();
          }
        }
      }
    }
  }

  return result;
}

bool xmlNodeHasAttribute(const Poco::XML::Node* p_node, const XMLAttribute attribute)
{
  bool found = attribute.name.empty() && attribute.value.empty();

  if(!found && p_node && p_node->hasAttributes())
  {
    Poco::AutoPtr<Poco::XML::NamedNodeMap> p_attributes(p_node->attributes());

    for (unsigned long i = 0; i < p_attributes->length() && !found; i++)
    {
      Poco::XML::Node* p_attribute = p_attributes->item(i);

      if (p_attribute->nodeName() == attribute.name && p_attribute->nodeValue() == attribute.value)
      {
        found = true;
      }
    }
  }

  return found;
}




/***********************************************************************************************************************
 * Struct definitions: SystemConstants
 */


} // end namespace rws
} // end namespace abb
