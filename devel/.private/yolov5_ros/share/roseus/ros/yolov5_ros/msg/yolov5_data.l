;; Auto-generated. Do not edit!


(when (boundp 'yolov5_ros::yolov5_data)
  (if (not (find-package "YOLOV5_ROS"))
    (make-package "YOLOV5_ROS"))
  (shadow 'yolov5_data (find-package "YOLOV5_ROS")))
(unless (find-package "YOLOV5_ROS::YOLOV5_DATA")
  (make-package "YOLOV5_ROS::YOLOV5_DATA"))

(in-package "ROS")
;;//! \htmlinclude yolov5_data.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass yolov5_ros::yolov5_data
  :super ros::object
  :slots (_header _yolo_box_data _object_depth_data _line_data ))

(defmethod yolov5_ros::yolov5_data
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:yolo_box_data __yolo_box_data) (instance std_msgs::Float32MultiArray :init))
    ((:object_depth_data __object_depth_data) (instance std_msgs::Float32MultiArray :init))
    ((:line_data __line_data) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _yolo_box_data __yolo_box_data)
   (setq _object_depth_data __object_depth_data)
   (setq _line_data __line_data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:yolo_box_data
   (&rest __yolo_box_data)
   (if (keywordp (car __yolo_box_data))
       (send* _yolo_box_data __yolo_box_data)
     (progn
       (if __yolo_box_data (setq _yolo_box_data (car __yolo_box_data)))
       _yolo_box_data)))
  (:object_depth_data
   (&rest __object_depth_data)
   (if (keywordp (car __object_depth_data))
       (send* _object_depth_data __object_depth_data)
     (progn
       (if __object_depth_data (setq _object_depth_data (car __object_depth_data)))
       _object_depth_data)))
  (:line_data
   (&optional __line_data)
   (if __line_data (setq _line_data __line_data)) _line_data)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; std_msgs/Float32MultiArray _yolo_box_data
    (send _yolo_box_data :serialization-length)
    ;; std_msgs/Float32MultiArray _object_depth_data
    (send _object_depth_data :serialization-length)
    ;; float32[] _line_data
    (* 4    (length _line_data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; std_msgs/Float32MultiArray _yolo_box_data
       (send _yolo_box_data :serialize s)
     ;; std_msgs/Float32MultiArray _object_depth_data
       (send _object_depth_data :serialize s)
     ;; float32[] _line_data
     (write-long (length _line_data) s)
     (dotimes (i (length _line_data))
       (sys::poke (elt _line_data i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; std_msgs/Float32MultiArray _yolo_box_data
     (send _yolo_box_data :deserialize buf ptr-) (incf ptr- (send _yolo_box_data :serialization-length))
   ;; std_msgs/Float32MultiArray _object_depth_data
     (send _object_depth_data :deserialize buf ptr-) (incf ptr- (send _object_depth_data :serialization-length))
   ;; float32[] _line_data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _line_data (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _line_data i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get yolov5_ros::yolov5_data :md5sum-) "1bc2c0993d921554a14c584cfa00945e")
(setf (get yolov5_ros::yolov5_data :datatype-) "yolov5_ros/yolov5_data")
(setf (get yolov5_ros::yolov5_data :definition-)
      "Header header
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
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
uint32 stride  # stride of given dimension
")



(provide :yolov5_ros/yolov5_data "1bc2c0993d921554a14c584cfa00945e")


