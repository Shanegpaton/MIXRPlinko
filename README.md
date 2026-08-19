# Plinko Simulation – C++ (Mixr Framework)

An interactive Plinko game built in **C++** with the **Mixr** framework, featuring custom collision logic for ball movement, pegs, and scoring.

---

## 🎯 Key Features

- **Custom Physics Engine**  
  - Real-time collision detection between balls and pegs.  
  - Ball-to-ball interaction with energy loss, bounce coefficients, and gravity effects.  
  - Supports multiple simultaneous moving balls.  
- **Animated Loading Screen** – Cycles through background images for a smooth GIF-like intro.  
- **Customizable Gameplay** – Change ball color, gravity, and bounce parameters via sliders.  
- **Score Tracking** – Automatically updates in real time.  

---

## 🛠 Technical Highlights

- **Language & Framework:** C++ with Mixr framework  
- **Physics Algorithms:**  
  - Elastic collision formulas for 2D circles.  
  - Continuous collision detection to prevent tunneling at high speeds.  
  - Adjustable gravity and restitution values.  
- **Rendering:**  
  - Animated background loop and event-driven controls.  
  - Event-driven UI updates for sliders, buttons, and scores.  

---

## 📸 Demo


🎥 **Watch the gameplay video here:** [Google Drive Link](https://drive.google.com/file/d/1jxkXG2gZLGN7-CgBptSLxmfvI2bkhFMJ/view?usp=sharing)  


---

## 🚀 How to Run

> **Note:** This project requires the **Mixr framework** to be **downloaded** on your system. Without Mixr, the application will not compile or run.

1. Download Mixr (refer to Mixr’s official documentation).  
2. Clone the repository:
   ```bash
   git clone https://github.com/your-username/plinko-mixr.git
   cd plinko-mixr
