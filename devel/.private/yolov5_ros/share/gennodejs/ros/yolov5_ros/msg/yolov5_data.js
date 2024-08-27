// Auto-generated. Do not edit!

// (in-package yolov5_ros.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class yolov5_data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.yolo_box_data = null;
      this.object_depth_data = null;
      this.line_data = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('yolo_box_data')) {
        this.yolo_box_data = initObj.yolo_box_data
      }
      else {
        this.yolo_box_data = new std_msgs.msg.Float32MultiArray();
      }
      if (initObj.hasOwnProperty('object_depth_data')) {
        this.object_depth_data = initObj.object_depth_data
      }
      else {
        this.object_depth_data = new std_msgs.msg.Float32MultiArray();
      }
      if (initObj.hasOwnProperty('line_data')) {
        this.line_data = initObj.line_data
      }
      else {
        this.line_data = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type yolov5_data
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [yolo_box_data]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.yolo_box_data, buffer, bufferOffset);
    // Serialize message field [object_depth_data]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.object_depth_data, buffer, bufferOffset);
    // Serialize message field [line_data]
    bufferOffset = _arraySerializer.float32(obj.line_data, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type yolov5_data
    let len;
    let data = new yolov5_data(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [yolo_box_data]
    data.yolo_box_data = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    // Deserialize message field [object_depth_data]
    data.object_depth_data = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    // Deserialize message field [line_data]
    data.line_data = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.yolo_box_data);
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.object_depth_data);
    length += 4 * object.line_data.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'yolov5_ros/yolov5_data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1bc2c0993d921554a14c584cfa00945e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    std_msgs/Float32MultiArray yolo_box_data
    std_msgs/Float32MultiArray object_depth_data
    float32[] line_data
    
    
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
    const resolved = new yolov5_data(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.yolo_box_data !== undefined) {
      resolved.yolo_box_data = std_msgs.msg.Float32MultiArray.Resolve(msg.yolo_box_data)
    }
    else {
      resolved.yolo_box_data = new std_msgs.msg.Float32MultiArray()
    }

    if (msg.object_depth_data !== undefined) {
      resolved.object_depth_data = std_msgs.msg.Float32MultiArray.Resolve(msg.object_depth_data)
    }
    else {
      resolved.object_depth_data = new std_msgs.msg.Float32MultiArray()
    }

    if (msg.line_data !== undefined) {
      resolved.line_data = msg.line_data;
    }
    else {
      resolved.line_data = []
    }

    return resolved;
    }
};

module.exports = yolov5_data;
