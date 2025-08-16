# File logger 🐶

<p> I developed a file logger for a hypothetical Linux-based embedded medical device designed for animals. The device is worn by a medium-sized dog. During setup, a patient profile is configured with attributes corresponding to the specific animal, which determines the normal operating ranges for key physiological parameters: body temperature, heart rate, and blood oxygen saturation (SpO₂).</p>
The output log file, `system.log`, records a notification whenever any of the monitored parameters fall outside the expected range for a medium-sized dog:

- Body Temperature: 37.7°C – 39.2°C
- Heart Rate: 60 – 100 bpm
- SpO₂: 97% – 100%

Since I didn't have access to real sensors or embedded hardware, I simulated the input by generating a `.csv` file containing random values for each monitored parameter.

