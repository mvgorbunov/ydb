# coding: utf-8

"""
    Kubernetes

    No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)  # noqa: E501

    The version of the OpenAPI document: release-1.30
    Generated by: https://openapi-generator.tech
"""


import pprint
import re  # noqa: F401

import six

from kubernetes.client.configuration import Configuration


class V1NodeRuntimeHandler(object):
    """NOTE: This class is auto generated by OpenAPI Generator.
    Ref: https://openapi-generator.tech

    Do not edit the class manually.
    """

    """
    Attributes:
      openapi_types (dict): The key is attribute name
                            and the value is attribute type.
      attribute_map (dict): The key is attribute name
                            and the value is json key in definition.
    """
    openapi_types = {
        'features': 'V1NodeRuntimeHandlerFeatures',
        'name': 'str'
    }

    attribute_map = {
        'features': 'features',
        'name': 'name'
    }

    def __init__(self, features=None, name=None, local_vars_configuration=None):  # noqa: E501
        """V1NodeRuntimeHandler - a model defined in OpenAPI"""  # noqa: E501
        if local_vars_configuration is None:
            local_vars_configuration = Configuration()
        self.local_vars_configuration = local_vars_configuration

        self._features = None
        self._name = None
        self.discriminator = None

        if features is not None:
            self.features = features
        if name is not None:
            self.name = name

    @property
    def features(self):
        """Gets the features of this V1NodeRuntimeHandler.  # noqa: E501


        :return: The features of this V1NodeRuntimeHandler.  # noqa: E501
        :rtype: V1NodeRuntimeHandlerFeatures
        """
        return self._features

    @features.setter
    def features(self, features):
        """Sets the features of this V1NodeRuntimeHandler.


        :param features: The features of this V1NodeRuntimeHandler.  # noqa: E501
        :type: V1NodeRuntimeHandlerFeatures
        """

        self._features = features

    @property
    def name(self):
        """Gets the name of this V1NodeRuntimeHandler.  # noqa: E501

        Runtime handler name. Empty for the default runtime handler.  # noqa: E501

        :return: The name of this V1NodeRuntimeHandler.  # noqa: E501
        :rtype: str
        """
        return self._name

    @name.setter
    def name(self, name):
        """Sets the name of this V1NodeRuntimeHandler.

        Runtime handler name. Empty for the default runtime handler.  # noqa: E501

        :param name: The name of this V1NodeRuntimeHandler.  # noqa: E501
        :type: str
        """

        self._name = name

    def to_dict(self):
        """Returns the model properties as a dict"""
        result = {}

        for attr, _ in six.iteritems(self.openapi_types):
            value = getattr(self, attr)
            if isinstance(value, list):
                result[attr] = list(map(
                    lambda x: x.to_dict() if hasattr(x, "to_dict") else x,
                    value
                ))
            elif hasattr(value, "to_dict"):
                result[attr] = value.to_dict()
            elif isinstance(value, dict):
                result[attr] = dict(map(
                    lambda item: (item[0], item[1].to_dict())
                    if hasattr(item[1], "to_dict") else item,
                    value.items()
                ))
            else:
                result[attr] = value

        return result

    def to_str(self):
        """Returns the string representation of the model"""
        return pprint.pformat(self.to_dict())

    def __repr__(self):
        """For `print` and `pprint`"""
        return self.to_str()

    def __eq__(self, other):
        """Returns true if both objects are equal"""
        if not isinstance(other, V1NodeRuntimeHandler):
            return False

        return self.to_dict() == other.to_dict()

    def __ne__(self, other):
        """Returns true if both objects are not equal"""
        if not isinstance(other, V1NodeRuntimeHandler):
            return True

        return self.to_dict() != other.to_dict()
