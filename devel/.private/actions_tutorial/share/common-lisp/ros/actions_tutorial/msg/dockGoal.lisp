; Auto-generated. Do not edit!


(cl:in-package actions_tutorial-msg)


;//! \htmlinclude dockGoal.msg.html

(cl:defclass <dockGoal> (roslisp-msg-protocol:ros-message)
  ((number_of_minutes
    :reader number_of_minutes
    :initarg :number_of_minutes
    :type cl:integer
    :initform 0))
)

(cl:defclass dockGoal (<dockGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <dockGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'dockGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name actions_tutorial-msg:<dockGoal> is deprecated: use actions_tutorial-msg:dockGoal instead.")))

(cl:ensure-generic-function 'number_of_minutes-val :lambda-list '(m))
(cl:defmethod number_of_minutes-val ((m <dockGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader actions_tutorial-msg:number_of_minutes-val is deprecated.  Use actions_tutorial-msg:number_of_minutes instead.")
  (number_of_minutes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <dockGoal>) ostream)
  "Serializes a message object of type '<dockGoal>"
  (cl:let* ((signed (cl:slot-value msg 'number_of_minutes)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <dockGoal>) istream)
  "Deserializes a message object of type '<dockGoal>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'number_of_minutes) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<dockGoal>)))
  "Returns string type for a message object of type '<dockGoal>"
  "actions_tutorial/dockGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'dockGoal)))
  "Returns string type for a message object of type 'dockGoal"
  "actions_tutorial/dockGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<dockGoal>)))
  "Returns md5sum for a message object of type '<dockGoal>"
  "08fc95c12e8d6b627afb5f6c3337b8ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'dockGoal)))
  "Returns md5sum for a message object of type 'dockGoal"
  "08fc95c12e8d6b627afb5f6c3337b8ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<dockGoal>)))
  "Returns full string definition for message of type '<dockGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Goal~%int32 number_of_minutes~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'dockGoal)))
  "Returns full string definition for message of type 'dockGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Goal~%int32 number_of_minutes~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <dockGoal>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <dockGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'dockGoal
    (cl:cons ':number_of_minutes (number_of_minutes msg))
))
