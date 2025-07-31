// Game variables
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const scoreElement = document.getElementById('score');
const highScoreElement = document.getElementById('high-score');
const gameOverScreen = document.getElementById('gameOver');
const finalScoreElement = document.getElementById('finalScore');
const restartBtn = document.getElementById('restartBtn');
const startScreen = document.getElementById('startScreen');
const startBtn = document.getElementById('startBtn');

// Touch controls
const upBtn = document.getElementById('upBtn');
const downBtn = document.getElementById('downBtn');
const leftBtn = document.getElementById('leftBtn');
const rightBtn = document.getElementById('rightBtn');

// Game settings
const GRID_SIZE = 20;
let CANVAS_WIDTH = 400;
let CANVAS_HEIGHT = 400;

// Game state
let snake = [];
let direction = { x: 0, y: 0 };
let food = {};
let score = 0;
let highScore = localStorage.getItem('snakeHighScore') || 0;
let gameRunning = false;
let gameLoop;

// Initialize game
function init() {
    // Set canvas size based on screen
    updateCanvasSize();
    
    // Set high score display
    highScoreElement.textContent = `High: ${highScore}`;
    
    // Event listeners
    window.addEventListener('resize', updateCanvasSize);
    document.addEventListener('keydown', handleKeyPress);
    
    // Touch controls
    upBtn.addEventListener('touchstart', (e) => { e.preventDefault(); changeDirection(0, -1); });
    downBtn.addEventListener('touchstart', (e) => { e.preventDefault(); changeDirection(0, 1); });
    leftBtn.addEventListener('touchstart', (e) => { e.preventDefault(); changeDirection(-1, 0); });
    rightBtn.addEventListener('touchstart', (e) => { e.preventDefault(); changeDirection(1, 0); });
    
    // Mouse controls for desktop testing
    upBtn.addEventListener('click', () => changeDirection(0, -1));
    downBtn.addEventListener('click', () => changeDirection(0, 1));
    leftBtn.addEventListener('click', () => changeDirection(-1, 0));
    rightBtn.addEventListener('click', () => changeDirection(1, 0));
    
    restartBtn.addEventListener('click', restartGame);
    startBtn.addEventListener('click', startGame);
    
    // Prevent scrolling on mobile
    document.addEventListener('touchmove', (e) => e.preventDefault(), { passive: false });
}

function updateCanvasSize() {
    const maxWidth = Math.min(window.innerWidth * 0.9, 400);
    const maxHeight = Math.min(window.innerHeight * 0.6, 400);
    
    CANVAS_WIDTH = Math.floor(maxWidth / GRID_SIZE) * GRID_SIZE;
    CANVAS_HEIGHT = Math.floor(maxHeight / GRID_SIZE) * GRID_SIZE;
    
    canvas.width = CANVAS_WIDTH;
    canvas.height = CANVAS_HEIGHT;
}

function startGame() {
    startScreen.classList.add('hidden');
    resetGame();
    gameRunning = true;
    gameLoop = setInterval(update, 100);
}

function resetGame() {
    snake = [
        { x: Math.floor(CANVAS_WIDTH / GRID_SIZE / 2) * GRID_SIZE, y: Math.floor(CANVAS_HEIGHT / GRID_SIZE / 2) * GRID_SIZE }
    ];
    direction = { x: 0, y: 0 };
    score = 0;
    updateScore();
    generateFood();
}

function generateFood() {
    food = {
        x: Math.floor(Math.random() * (CANVAS_WIDTH / GRID_SIZE)) * GRID_SIZE,
        y: Math.floor(Math.random() * (CANVAS_HEIGHT / GRID_SIZE)) * GRID_SIZE
    };
    
    // Ensure food doesn't spawn on snake
    for (let segment of snake) {
        if (segment.x === food.x && segment.y === food.y) {
            generateFood();
            break;
        }
    }
}

function update() {
    if (!gameRunning) return;
    
    // Move snake head
    const head = { x: snake[0].x + direction.x * GRID_SIZE, y: snake[0].y + direction.y * GRID_SIZE };
    
    // Check wall collision
    if (head.x < 0 || head.x >= CANVAS_WIDTH || head.y < 0 || head.y >= CANVAS_HEIGHT) {
        gameOver();
        return;
    }
    
    // Check self collision
    for (let segment of snake) {
        if (head.x === segment.x && head.y === segment.y) {
            gameOver();
            return;
        }
    }
    
    snake.unshift(head);
    
    // Check food collision
    if (head.x === food.x && head.y === food.y) {
        score += 10;
        updateScore();
        generateFood();
    } else {
        snake.pop();
    }
    
    draw();
}

function draw() {
    // Clear canvas
    ctx.fillStyle = '#1a1a2e';
    ctx.fillRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    
    // Draw snake
    ctx.fillStyle = '#4CAF50';
    for (let i = 0; i < snake.length; i++) {
        const segment = snake[i];
        ctx.fillRect(segment.x, segment.y, GRID_SIZE - 2, GRID_SIZE - 2);
        
        // Draw eyes on head
        if (i === 0) {
            ctx.fillStyle = '#1a1a2e';
            const eyeSize = 3;
            const eyeOffset = 5;
            ctx.fillRect(segment.x + eyeOffset, segment.y + eyeOffset, eyeSize, eyeSize);
            ctx.fillRect(segment.x + GRID_SIZE - eyeOffset - eyeSize, segment.y + eyeOffset, eyeSize, eyeSize);
            ctx.fillStyle = '#4CAF50';
        }
    }
    
    // Draw food
    ctx.fillStyle = '#FF5722';
    ctx.beginPath();
    ctx.arc(food.x + GRID_SIZE / 2, food.y + GRID_SIZE / 2, GRID_SIZE / 2 - 2, 0, Math.PI * 2);
    ctx.fill();
}

function handleKeyPress(e) {
    if (!gameRunning && e.key !== 'Enter') return;
    
    if (e.key === 'Enter' && !gameRunning) {
        if (!startScreen.classList.contains('hidden')) {
            startGame();
        } else {
            restartGame();
        }
        return;
    }
    
    switch (e.key) {
        case 'ArrowUp':
            changeDirection(0, -1);
            break;
        case 'ArrowDown':
            changeDirection(0, 1);
            break;
        case 'ArrowLeft':
            changeDirection(-1, 0);
            break;
        case 'ArrowRight':
            changeDirection(1, 0);
            break;
    }
}

function changeDirection(x, y) {
    if (!gameRunning) return;
    
    // Prevent reverse direction
    if (direction.x === -x && direction.y === -y) return;
    
    direction = { x, y };
}

function updateScore() {
    scoreElement.textContent = `Score: ${score}`;
}

function gameOver() {
    gameRunning = false;
    clearInterval(gameLoop);
    
    if (score > highScore) {
        highScore = score;
        localStorage.setItem('snakeHighScore', highScore);
        highScoreElement.textContent = `High: ${highScore}`;
    }
    
    finalScoreElement.textContent = `Score: ${score}`;
    gameOverScreen.classList.remove('hidden');
}

function restartGame() {
    gameOverScreen.classList.add('hidden');
    resetGame();
    gameRunning = true;
    gameLoop = setInterval(update, 100);
}

// Initialize when page loads
window.addEventListener('load', init);