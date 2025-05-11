<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Game README</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 40px;
            background-color: #f4f4f4;
            color: #333;
        }
        h1, h2 {
            color: #2c3e50;
        }
        h3 {
            color: #2980b9;
        }
        code {
            background-color: #ecf0f1;
            padding: 5px;
            border-radius: 4px;
        }
        ul {
            list-style-type: none;
            padding: 0;
        }
        li {
            margin: 8px 0;
        }
        .highlight {
            background-color: #e74c3c;
            color: white;
            padding: 2px 5px;
            border-radius: 4px;
        }
        .section {
            margin-bottom: 30px;
        }
    </style>
</head>
<body>

    <h1>Whack-a-Mole Game README</h1>

    <div class="section">
        <h2>Introduction</h2>
        <p>This is a fun and interactive "Whack-a-Mole" game built using SDL2. In the game, you click on various moles that appear on the screen to earn points while avoiding obstacles. The game features multiple states such as Start, Settings, Playing, Pause, and Game Over.</p>
    </div>

    <div class="section">
        <h2>Features</h2>
        <ul>
            <li>Interactive Whack-a-Mole gameplay with animated sprites.</li>
            <li>Volume control for music and sound effects.</li>
            <li>Multiple game states including Start Screen, Settings, Info Screen, Playing, Pause, and Game Over.</li>
            <li>High score saving and loading functionality.</li>
            <li>Responsive GUI elements such as buttons and sliders.</li>
        </ul>
    </div>

    <div class="section">
        <h2>Installation</h2>
        <p>To run this game, you'll need to set up SDL2 and the required libraries. Follow the steps below:</p>
        <ul>
            <li>Install <strong>SDL2</strong> and the SDL2_mixer library.</li>
            <li>Clone this repository using:
                <br><code>git clone https://github.com/your-username/whack-a-mole.git</code>
            </li>
            <li>Navigate to the project directory and compile the game with:
                <br><code>g++ -o whack-a-mole main.cpp -lSDL2 -lSDL2_mixer</code>
            </li>
            <li>Run the compiled game:
                <br><code>./whack-a-mole</code>
            </li>
        </ul>
    </div>

    <div class="section">
        <h2>Game Controls</h2>
        <ul>
            <li><strong>Mouse:</strong> Click on the moles to score points.</li>
            <li><strong>Settings:</strong> Adjust the music and sound effect volumes in the settings menu.</li>
            <li><strong>Pause:</strong> Pause the game and return to the Start Screen or Resume from the pause menu.</li>
        </ul>
    </div>

    <div class="section">
        <h2>Game Screens</h2>
        <h3>Start Screen</h3>
        <p>Welcome screen with the option to play the game or go to the settings menu.</p>
        
        <h3>Settings Screen</h3>
        <p>Adjust the volume for music and sound effects. Select the music option for the background music.</p>

        <h3>Playing Screen</h3>
        <p>Game in progress, click on the moles that appear to score points while avoiding obstacles.</p>

        <h3>Pause Screen</h3>
        <p>Pause the game and return to the start or resume playing.</p>

        <h3>Game Over Screen</h3>
        <p>Game over screen showing your score and high score.</p>
    </div>

    <div class="section">
        <h2>Code Structure</h2>
        <p>The game is organized into different classes and files for better modularity:</p>
        <ul>
            <li><strong>Game.cpp</strong>: Main game logic including initialization, event handling, and state management.</li>
            <li><strong>Stat.cpp</strong>: Manages game statistics, including score, lives, and high score.</li>
            <li><strong>Graphics.cpp</strong>: Handles rendering of textures, animations, and UI elements.</li>
        </ul>
    </div>

    <div class="section">
        <h2>Contributing</h2>
        <p>Feel free to fork the project, make changes, and create pull requests. Contributions are welcome!</p>
    </div>

    <div class="section">
        <h2>License</h2>
        <p>This project is licensed under the <span class="highlight">MIT License</span> - see the LICENSE file for details.</p>
    </div>

</body>
</html>
