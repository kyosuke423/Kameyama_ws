
(cl:in-package :asdf)

(defsystem "yolov5_ros-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "yolov5_data" :depends-on ("_package_yolov5_data"))
    (:file "_package_yolov5_data" :depends-on ("_package"))
  ))