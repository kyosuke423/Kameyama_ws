
(cl:in-package :asdf)

(defsystem "line_msg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "LinePoint" :depends-on ("_package_LinePoint"))
    (:file "_package_LinePoint" :depends-on ("_package"))
  ))