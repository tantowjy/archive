import cv2

# Initialize the camera
cap = cv2.VideoCapture(0)  # Use 0 for default camera, you can change this if needed

# Initialize variables
prev_frame = None
motion_direction = None

while True:
    ret, frame = cap.read()

    if not ret:
        break

    # Convert frame to grayscale for motion detection
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray_frame = cv2.GaussianBlur(gray_frame, (21, 21), 0)  # Apply Gaussian blur to reduce noise

    if prev_frame is None:
        prev_frame = gray_frame
        continue

    # Calculate the absolute difference between the current frame and the previous frame
    frame_delta = cv2.absdiff(prev_frame, gray_frame)
    thresh = cv2.threshold(frame_delta, 25, 255, cv2.THRESH_BINARY)[1]
    thresh = cv2.dilate(thresh, None, iterations=2)

    # Find contours of moving objects
    contours, _ = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        if cv2.contourArea(contour) < 1000:  # Adjust this threshold as needed
            continue

        (x, y, w, h) = cv2.boundingRect(contour)
        #cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        if y > prev_frame.shape[0] / 2:
            motion_direction = "Top to Bottom"
        else:
            motion_direction = "Bottom to Top"

    # Display the frames and motion direction
    cv2.putText(frame, f"Motion Direction: {motion_direction}", (10, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    cv2.imshow("Camera Feed", frame)

    prev_frame = gray_frame

    # Exit by pressing 'Q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
