import { Game } from './Game.js';

async function startGame() {
    const canvas = document.getElementById('gameCanvas');
    const game = new Game(canvas);
    
    try {
        await game.init();
        game.run();
        console.log('Whack-A-Mouse game started!');
    } catch (error) {
        console.error('Failed to start game:', error);
    }
}

// Start the game when the page loads
window.addEventListener('load', startGame);