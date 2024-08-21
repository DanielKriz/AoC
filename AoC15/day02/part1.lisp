(load "../common.lisp")

(defun gift-area (dimensions)
  (let ((sides (mapcar #'* dimensions (left-rotate dimensions))))
    (reduce #'+ (append (mapcar (lambda(i) (* 2 i)) sides) (cons (smallest sides) ())))))

(defun main ()
  (let ((gifts
          (remove nil (loop for gift = (read *standard-input* nil nil)
            collect (if gift (mapcar 'parse-integer (split-by-delimeter (string gift) #\X)))
            while gift))))
    (write (reduce #'+ (mapcar 'gift-area gifts)))))
