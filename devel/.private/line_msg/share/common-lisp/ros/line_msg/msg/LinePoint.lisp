; Auto-generated. Do not edit!


(cl:in-package line_msg-msg)


;//! \htmlinclude LinePoint.msg.html

(cl:defclass <LinePoint> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (startx
    :reader startx
    :initarg :startx
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray))
   (starty
    :reader starty
    :initarg :starty
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray))
   (endx
    :reader endx
    :initarg :endx
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray))
   (endy
    :reader endy
    :initarg :endy
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray)))
)

(cl:defclass LinePoint (<LinePoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LinePoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LinePoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name line_msg-msg:<LinePoint> is deprecated: use line_msg-msg:LinePoint instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <LinePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader line_msg-msg:header-val is deprecated.  Use line_msg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'startx-val :lambda-list '(m))
(cl:defmethod startx-val ((m <LinePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader line_msg-msg:startx-val is deprecated.  Use line_msg-msg:startx instead.")
  (startx m))

(cl:ensure-generic-function 'starty-val :lambda-list '(m))
(cl:defmethod starty-val ((m <LinePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader line_msg-msg:starty-val is deprecated.  Use line_msg-msg:starty instead.")
  (starty m))

(cl:ensure-generic-function 'endx-val :lambda-list '(m))
(cl:defmethod endx-val ((m <LinePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader line_msg-msg:endx-val is deprecated.  Use line_msg-msg:endx instead.")
  (endx m))

(cl:ensure-generic-function 'endy-val :lambda-list '(m))
(cl:defmethod endy-val ((m <LinePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader line_msg-msg:endy-val is deprecated.  Use line_msg-msg:endy instead.")
  (endy m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LinePoint>) ostream)
  "Serializes a message object of type '<LinePoint>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'startx) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'starty) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'endx) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'endy) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LinePoint>) istream)
  "Deserializes a message object of type '<LinePoint>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'startx) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'starty) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'endx) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'endy) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LinePoint>)))
  "Returns string type for a message object of type '<LinePoint>"
  "line_msg/LinePoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LinePoint)))
  "Returns string type for a message object of type 'LinePoint"
  "line_msg/LinePoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LinePoint>)))
  "Returns md5sum for a message object of type '<LinePoint>"
  "1aadf4bb8a6f95a32166f6069d5187f4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LinePoint)))
  "Returns md5sum for a message object of type 'LinePoint"
  "1aadf4bb8a6f95a32166f6069d5187f4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LinePoint>)))
  "Returns full string definition for message of type '<LinePoint>"
  (cl:format cl:nil "Header header~%std_msgs/Float32MultiArray startx~%std_msgs/Float32MultiArray starty~%std_msgs/Float32MultiArray endx~%std_msgs/Float32MultiArray endy~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LinePoint)))
  "Returns full string definition for message of type 'LinePoint"
  (cl:format cl:nil "Header header~%std_msgs/Float32MultiArray startx~%std_msgs/Float32MultiArray starty~%std_msgs/Float32MultiArray endx~%std_msgs/Float32MultiArray endy~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LinePoint>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'startx))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'starty))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'endx))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'endy))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LinePoint>))
  "Converts a ROS message object to a list"
  (cl:list 'LinePoint
    (cl:cons ':header (header msg))
    (cl:cons ':startx (startx msg))
    (cl:cons ':starty (starty msg))
    (cl:cons ':endx (endx msg))
    (cl:cons ':endy (endy msg))
))
