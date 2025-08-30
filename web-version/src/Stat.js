export class Stat {
    constructor() {
        this.score = 0;
        this.lives = 3;
        this.mxscore = 0;
        this.loadHighScore();
    }

    saveHighScore() {
        localStorage.setItem('whack-a-mouse-highscore', this.mxscore.toString());
    }

    loadHighScore() {
        const saved = localStorage.getItem('whack-a-mouse-highscore');
        this.mxscore = saved ? parseInt(saved) : 0;
    }

    updateHighScore() {
        if (this.score > this.mxscore) {
            this.mxscore = this.score;
            this.saveHighScore();
        }
    }

    resetGame() {
        this.score = 0;
        this.lives = 3;
    }
}