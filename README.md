## Introduction

This repository contains the code and documentation for a Raspberry Pi-based ALS (Advanced Life Support) simulator developed during the ALS-simulator hackathon. The simulator is designed to simulate vital signs using an ECG (Electrocardiogram), NIBP (Non-Invasive Blood Pressure), and temperature modules connected to a sensor hub via I2C communication.

## Features

- Simulates ECG signals
- Simulates NIBP measurements
- Simulates temperature readings

## Hardware Setup

To recreate the ALS simulator, you'll need the following hardware:

- Raspberry Pi
- Sensor Hub
- ECG Module
- NIBP Module
- Temperature Module
- 4 pin leads
- 6 pin leads

Connect the ECG, NIBP, and temperature modules to the sensor hub using the provided connectors and leads. The sensor hub communicates with the Raspberry Pi over I2C.

## Usage

- Follow the hardware setup instructions.
- Install dependencies on your Raspberry Pi
- Run the software on your Raspberry Pi.
- Monitor the simulated vital signs using the ALS simulator.

## Contributing

If you'd like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature`.
3. Commit your changes: `git commit -m 'Add some feature'`.
4. Push to the branch: `git push origin feature/your-feature`.
5. Submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
