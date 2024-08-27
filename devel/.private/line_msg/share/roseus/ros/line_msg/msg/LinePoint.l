;; Auto-generated. Do not edit!


(when (boundp 'line_msg::LinePoint)
  (if (not (find-package "LINE_MSG"))
    (make-package "LINE_MSG"))
  (shadow 'LinePoint (find-package "LINE_MSG")))
(unless (find-package "LINE_MSG::LINEPOINT")
  (make-package "LINE_MSG::LINEPOINT"))

(in-package "ROS")
;;//! \htmlinclude LinePoint.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass line_msg::LinePoint
  :super ros::object
  :slots (_header _startx _starty _endx _endy ))

(defmethod line_msg::LinePoint
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:startx __startx) (instance std_msgs::Float32MultiArray :init))
    ((:starty __starty) (instance std_msgs::Float32MultiArray :init))
    ((:endx __endx) (instance std_msgs::Float32MultiArray :init))
    ((:endy __endy) (instance std_msgs::Float32MultiArray :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _startx __startx)
   (setq _starty __starty)
   (setq _endx __endx)
   (setq _endy __endy)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:startx
   (&rest __startx)
   (if (keywordp (car __startx))
       (send* _startx __startx)
     (progn
       (if __startx (setq _startx (car __startx)))
       _startx)))
  (:starty
   (&rest __starty)
   (if (keywordp (car __starty))
       (send* _starty __starty)
     (progn
       (if __starty (setq _starty (car __starty)))
       _starty)))
  (:endx
   (&rest __endx)
   (if (keywordp (car __endx))
       (send* _endx __endx)
     (progn
       (if __endx (setq _endx (car __endx)))
       _endx)))
  (:endy
   (&rest __endy)
   (if (keywordp (car __endy))
       (send* _endy __endy)
     (progn
       (if __endy (setq _endy (car __endy)))
       _endy)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; std_msgs/Float32MultiArray _startx
    (send _startx :serialization-length)
    ;; std_msgs/Float32MultiArray _starty
    (send _starty :serialization-length)
    ;; std_msgs/Float32MultiArray _endx
    (send _endx :serialization-length)
    ;; std_msgs/Float32MultiArray _endy
    (send _endy :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; std_msgs/Float32MultiArray _startx
       (send _startx :serialize s)
     ;; std_msgs/Float32MultiArray _starty
       (send _starty :serialize s)
     ;; std_msgs/Float32MultiArray _endx
       (send _endx :serialize s)
     ;; std_msgs/Float32MultiArray _endy
       (send _endy :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; std_msgs/Float32MultiArray _startx
     (send _startx :deserialize buf ptr-) (incf ptr- (send _startx :serialization-length))
   ;; std_msgs/Float32MultiArray _starty
     (send _starty :deserialize buf ptr-) (incf ptr- (send _starty :serialization-length))
   ;; std_msgs/Float32MultiArray _endx
     (send _endx :deserialize buf ptr-) (incf ptr- (send _endx :serialization-length))
   ;; std_msgs/Float32MultiArray _endy
     (send _endy :deserialize buf ptr-) (incf ptr- (send _endy :serialization-length))
   ;;
   self)
  )

(setf (get line_msg::LinePoint :md5sum-) "1aadf4bb8a6f95a32166f6069d5187f4")
(setf (get line_msg::LinePoint :datatype-) "line_msg/LinePoint")
(setf (get line_msg::LinePoint :definition-)
      "Header header
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



(provide :line_msg/LinePoint "1aadf4bb8a6f95a32166f6069d5187f4")


