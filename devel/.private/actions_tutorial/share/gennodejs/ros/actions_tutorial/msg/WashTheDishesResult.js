// Auto-generated. Do not edit!

// (in-package actions_tutorial.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class WashTheDishesResult {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.dishes_washed = null;
    }
    else {
      if (initObj.hasOwnProperty('dishes_washed')) {
        this.dishes_washed = initObj.dishes_washed
      }
      else {
        this.dishes_washed = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type WashTheDishesResult
    // Serialize message field [dishes_washed]
    bufferOffset = _arraySerializer.string(obj.dishes_washed, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type WashTheDishesResult
    let len;
    let data = new WashTheDishesResult(null);
    // Deserialize message field [dishes_washed]
    data.dishes_washed = _arrayDeserializer.string(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.dishes_washed.forEach((val) => {
      length += 4 + val.length;
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'actions_tutorial/WashTheDishesResult';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '71ead59b8b061c1cfe7f297d0e32bef2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    # Result
    string[] dishes_washed
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new WashTheDishesResult(null);
    if (msg.dishes_washed !== undefined) {
      resolved.dishes_washed = msg.dishes_washed;
    }
    else {
      resolved.dishes_washed = []
    }

    return resolved;
    }
};

module.exports = WashTheDishesResult;
