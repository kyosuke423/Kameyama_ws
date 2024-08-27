;; Auto-generated. Do not edit!


(when (boundp 'tutorial_python::multiplier)
  (if (not (find-package "TUTORIAL_PYTHON"))
    (make-package "TUTORIAL_PYTHON"))
  (shadow 'multiplier (find-package "TUTORIAL_PYTHON")))
(unless (find-package "TUTORIAL_PYTHON::MULTIPLIER")
  (make-package "TUTORIAL_PYTHON::MULTIPLIER"))
(unless (find-package "TUTORIAL_PYTHON::MULTIPLIERREQUEST")
  (make-package "TUTORIAL_PYTHON::MULTIPLIERREQUEST"))
(unless (find-package "TUTORIAL_PYTHON::MULTIPLIERRESPONSE")
  (make-package "TUTORIAL_PYTHON::MULTIPLIERRESPONSE"))

(in-package "ROS")





(defclass tutorial_python::multiplierRequest
  :super ros::object
  :slots (_a _b ))

(defmethod tutorial_python::multiplierRequest
  (:init
   (&key
    ((:a __a) 0)
    ((:b __b) 0)
    )
   (send-super :init)
   (setq _a (round __a))
   (setq _b (round __b))
   self)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:b
   (&optional __b)
   (if __b (setq _b __b)) _b)
  (:serialization-length
   ()
   (+
    ;; int32 _a
    4
    ;; int32 _b
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _a
       (write-long _a s)
     ;; int32 _b
       (write-long _b s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _a
     (setq _a (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _b
     (setq _b (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass tutorial_python::multiplierResponse
  :super ros::object
  :slots (_result ))

(defmethod tutorial_python::multiplierResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; int32 _result
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _result
       (write-long _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _result
     (setq _result (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass tutorial_python::multiplier
  :super ros::object
  :slots ())

(setf (get tutorial_python::multiplier :md5sum-) "a7d7d7065d45755acef7d4dcf908162a")
(setf (get tutorial_python::multiplier :datatype-) "tutorial_python/multiplier")
(setf (get tutorial_python::multiplier :request) tutorial_python::multiplierRequest)
(setf (get tutorial_python::multiplier :response) tutorial_python::multiplierResponse)

(defmethod tutorial_python::multiplierRequest
  (:response () (instance tutorial_python::multiplierResponse :init)))

(setf (get tutorial_python::multiplierRequest :md5sum-) "a7d7d7065d45755acef7d4dcf908162a")
(setf (get tutorial_python::multiplierRequest :datatype-) "tutorial_python/multiplierRequest")
(setf (get tutorial_python::multiplierRequest :definition-)
      "int32 a
int32 b
---
int32 result
")

(setf (get tutorial_python::multiplierResponse :md5sum-) "a7d7d7065d45755acef7d4dcf908162a")
(setf (get tutorial_python::multiplierResponse :datatype-) "tutorial_python/multiplierResponse")
(setf (get tutorial_python::multiplierResponse :definition-)
      "int32 a
int32 b
---
int32 result
")



(provide :tutorial_python/multiplier "a7d7d7065d45755acef7d4dcf908162a")


