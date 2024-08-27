
(cl:in-package :asdf)

(defsystem "tutorial_python-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "multiplier" :depends-on ("_package_multiplier"))
    (:file "_package_multiplier" :depends-on ("_package"))
  ))