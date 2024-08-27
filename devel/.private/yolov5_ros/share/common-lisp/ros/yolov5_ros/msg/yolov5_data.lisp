; Auto-generated. Do not edit!


(cl:in-package yolov5_ros-msg)


;//! \htmlinclude yolov5_data.msg.html

(cl:defclass <yolov5_data> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (yolo_box_data
    :reader yolo_box_data
    :initarg :yolo_box_data
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray))
   (object_depth_data
    :reader object_depth_data
    :initarg :object_depth_data
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray))
   (line_data
    :reader line_data
    :initarg :line_data
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass yolov5_data (<yolov5_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <yolov5_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'yolov5_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name yolov5_ros-msg:<yolov5_data> is deprecated: use yolov5_ros-msg:yolov5_data instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <yolov5_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader yolov5_ros-msg:header-val is deprecated.  Use yolov5_ros-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'yolo_box_data-val :lambda-list '(m))
(cl:defmethod yolo_box_data-val ((m <yolov5_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader yolov5_ros-msg:yolo_box_data-val is deprecated.  Use yolov5_ros-msg:yolo_box_data instead.")
  (yolo_box_data m))

(cl:ensure-generic-function 'object_depth_data-val :lambda-list '(m))
(cl:defmethod object_depth_data-val ((m <yolov5_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader yolov5_ros-msg:object_depth_data-val is deprecated.  Use yolov5_ros-msg:object_depth_data instead.")
  (object_depth_data m))

(cl:ensure-generic-function 'line_data-val :lambda-list '(m))
(cl:defmethod line_data-val ((m <yolov5_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader yolov5_ros-msg:line_data-val is deprecated.  Use yolov5_ros-msg:line_data instead.")
  (line_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <yolov5_data>) ostream)
  "Serializes a message object of type '<yolov5_data>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'yolo_box_data) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'object_depth_data) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'line_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'line_data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <yolov5_data>) istream)
  "Deserializes a message object of type '<yolov5_data>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'yolo_box_data) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'object_depth_data) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'line_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'line_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<yolov5_data>)))
  "Returns string type for a message object of type '<yolov5_data>"
  "yolov5_ros/yolov5_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'yolov5_data)))
  "Returns string type for a message object of type 'yolov5_data"
  "yolov5_ros/yolov5_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<yolov5_data>)))
  "Returns md5sum for a message object of type '<yolov5_data>"
  "1bc2c0993d921554a14c584cfa00945e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'yolov5_data)))
  "Returns md5sum for a message object of type 'yolov5_data"
  "1bc2c0993d921554a14c584cfa00945e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<yolov5_data>)))
  "Returns full string definition for message of type '<yolov5_data>"
  (cl:format cl:nil "Header header~%std_msgs/Float32MultiArray yolo_box_data~%std_msgs/Float32MultiArray object_depth_data~%float32[] line_data~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'yolov5_data)))
  "Returns full string definition for message of type 'yolov5_data"
  (cl:format cl:nil "Header header~%std_msgs/Float32MultiArray yolo_box_data~%std_msgs/Float32MultiArray object_depth_data~%float32[] line_data~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <yolov5_data>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'yolo_box_data))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'object_depth_data))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'line_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <yolov5_data>))
  "Converts a ROS message object to a list"
  (cl:list 'yolov5_data
    (cl:cons ':header (header msg))
    (cl:cons ':yolo_box_data (yolo_box_data msg))
    (cl:cons ':object_depth_data (object_depth_data msg))
    (cl:cons ':line_data (line_data msg))
))
