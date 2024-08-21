(load "../common.lisp")

(defun ribbon-len (dimensions)
  (let ((dimensions (sort dimensions #'<)))
    (reduce #'+
      (append
        (list
          (reduce #'* dimensions))
          (mapcar (lambda(i) (* 2 i)) (list(pop dimensions) (pop dimensions)))))))

(defun main ()
  (let ((gifts
          (remove nil (loop for gift = (read *standard-input* nil nil)
            collect (if gift (mapcar 'parse-integer (split-by-delimeter (string gift) #\X)))
            while gift))))
    (write (reduce #'+ (mapcar 'ribbon-len gifts)))))
