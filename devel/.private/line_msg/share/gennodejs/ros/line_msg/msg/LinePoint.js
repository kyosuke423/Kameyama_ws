// Auto-generated. Do not edit!

// (in-package line_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class LinePoint {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.startx = null;
      this.starty = null;
      this.endx = null;
      this.endy = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('startx')) {
        this.startx = initObj.startx
      }
      else {
        this.startx = new std_msgs.msg.Float32MultiArray();
      }
      if (initObj.hasOwnProperty('starty')) {
        this.starty = initObj.starty
      }
      else {
        this.starty = new std_msgs.msg.Float32MultiArray();
      }
      if (initObj.hasOwnProperty('endx')) {
        this.endx = initObj.endx
      }
      else {
        this.endx = new std_msgs.msg.Float32MultiArray();
      }
      if (initObj.hasOwnProperty('endy')) {
        this.endy = initObj.endy
      }
      else {
        this.endy = new std_msgs.msg.Float32MultiArray();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LinePoint
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [startx]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.startx, buffer, bufferOffset);
    // Serialize message field [starty]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.starty, buffer, bufferOffset);
    // Serialize message field [endx]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.endx, buffer, bufferOffset);
    // Serialize message field [endy]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.endy, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LinePoint
    let len;
    let data = new LinePoint(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [startx]
    data.startx = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    // Deserialize message field [starty]
    data.starty = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    // Deserialize message field [endx]
    data.endx = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    // Deserialize message field [endy]
    data.endy = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.startx);
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.starty);
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.endx);
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.endy);
    return length;
  }

  static datatype() {
    // Returns string type for a message object
    return 'line_msg/LinePoint';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1aadf4bb8a6f95a32166f6069d5187f4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    std_msgs/Float32MultiArray startx
    std_msgs/Float32MultiArray starty
    std_msgs/Float32MultiArray endx
    std_msgs/Float32MultiArray endy
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: std_msgs/Float32MultiArray
    # Please look at the MultiArrayLayout message definition for
    # documentation on all multiarrays.
    
    MultiArrayLayout  layout        # specification of data layout
    float32[]         data          # array of data
    
    
    ================================================================================
    MSG: std_msgs/MultiArrayLayout
    # The multiarray declares a generic multi-dimensional array of a
    # particular data type.  Dimensions are ordered from outer most
    # to inner most.
    
    MultiArrayDimension[] dim # Array of dimension properties
    uint32 data_offset        # padding elements at front of data
    
    # Accessors should ALWAYS be written in terms of dimension stride
    # and specified outer-most dimension first.
    # 
    # multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
    #
    # A standard, 3-channel 640x480 image with interleaved color channels
    # would be specified as:
    #
    # dim[0].label  = "height"
    # dim[0].size   = 480
    # dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
    # dim[1].label  = "width"
    # dim[1].size   = 640
    # dim[1].stride = 3*640 = 1920
    # dim[2].label  = "channel"
    # dim[2].size   = 3
    # dim[2].stride = 3
    #
    # multiarray(i,j,k) refers to the ith row, jth column, and kth channel.
    
    ================================================================================
    MSG: std_msgs/MultiArrayDimension
    string label   # label of given dimension
    uint32 size    # size of given dimension (in type units)
    uint32 stride  # stride of given dimension
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LinePoint(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.startx !== undefined) {
      resolved.startx = std_msgs.msg.Float32MultiArray.Resolve(msg.startx)
    }
    else {
      resolved.startx = new std_msgs.msg.Float32MultiArray()
    }

    if (msg.starty !== undefined) {
      resolved.starty = std_msgs.msg.Float32MultiArray.Resolve(msg.starty)
    }
    else {
      resolved.starty = new std_msgs.msg.Float32MultiArray()
    }

    if (msg.endx !== undefined) {
      resolved.endx = std_msgs.msg.Float32MultiArray.Resolve(msg.endx)
    }
    else {
      resolved.endx = new std_msgs.msg.Float32MultiArray()
    }

    if (msg.endy !== undefined) {
      resolved.endy = std_msgs.msg.Float32MultiArray.Resolve(msg.endy)
    }
    else {
      resolved.endy = new std_msgs.msg.Float32MultiArray()
    }

    return resolved;
    }
};

module.exports = LinePoint;
