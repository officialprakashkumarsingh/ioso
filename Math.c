<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Speed Racer - Car Racing Game</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="game-container">
        <div class="game-header">
            <h1>Speed Racer</h1>
            <div class="score-display">
                <span>Score: <span id="score">0</span></span>
                <span>Speed: <span id="speed">1</span>x</span>
            </div>
        </div>
        
        <div id="gameCanvas" class="game-canvas">
            <div id="playerCar" class="car player-car"></div>
            <div id="roadLines"></div>
            <div id="enemyCars"></div>
        </div>
        
        <div id="gameOver" class="game-over hidden">
            <h2>Game Over!</h2>
            <p>Final Score: <span id="finalScore">0</span></p>
            <button onclick="restartGame()">Play Again</button>
        </div>
        
        <div id="startScreen" class="start-screen">
            <h2>Speed Racer</h2>
            <p>Use ← → arrow keys to move</p>
            <p>Avoid the enemy cars!</p>
            <button onclick="startGame()">Start Game</button>
        </div>
    </div>

    <script src="game.js"></script>
</body>
</html>