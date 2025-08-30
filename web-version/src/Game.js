import { Graphics } from './Graphics.js';
import { Mouse } from './Mouse.js';
import { Column } from './Column.js';
import { Stat } from './Stat.js';
import { State } from './State.js';

export class Game {
    constructor(canvas) {
        this.graphics = new Graphics(canvas);
        this.stat = new Stat();
        this.curState = State.StartScreen;
        this.soundEnabled = true;
        this.newGame = true;
        this.clicked = false;
        this.spawnInterval = 2000;
        this.idx = 1;
        this.isRunning = true;
        this.lastSpawnTime = 0;
        this.musicX = 80;
        this.sfxX = 80;
        
        // Mouse positions
        this.xBasechuot = [110, 170, 250, 320];
        this.xBasemeo = [80, 150, 220, 300];
        
        // Game columns
        this.cot = [
            new Column(100, 170, 350, 800),
            new Column(175, 240, 350, 800),
            new Column(241, 313, 350, 800),
            new Column(314, 390, 350, 800)
        ];
        
        // UI buttons
        this.nutBatDau = new Column(100, 400, 550, 638);
        this.nutInfo = new Column(10, 60, 20, 70);
        this.tatInfo = new Column(360, 400, 200, 250);
        this.nutPlayAgain = new Column(100, 400, 550, 638);
        this.nutPause = new Column(400, 450, 10, 60);
        this.nutResume = new Column(150, 300, 480, 540);
        this.nutHome = new Column(150, 300, 570, 630);
        this.vlbar = new Column(90, 362, 280, 300);
        this.sfxbar = new Column(90, 362, 390, 410);
        this.nutSet = new Column(400, 450, 10, 55);
        this.m1 = new Column(150, 170, 500, 520);
        this.m2 = new Column(250, 270, 500, 520);
        this.m3 = new Column(380, 400, 500, 520);
        
        this.mouse = [];
        this.textures = {};
        this.sounds = {};
        this.music = {};
        
        this.dragvol = false;
        this.dragsfx = false;
        this.muzik = false;
    }

    async init() {
        // Load all textures
        this.textures.background = await this.graphics.loadTexture('assets/picture/background.jpg');
        this.textures.play = await this.graphics.loadTexture('assets/picture/play.png');
        this.textures.playagain = await this.graphics.loadTexture('assets/picture/playagain.png');
        this.textures.board = await this.graphics.loadTexture('assets/picture/board.png');
        this.textures.meodungyen = await this.graphics.loadTexture('assets/picture/meodungyen.png');
        this.textures.meodap = await this.graphics.loadTexture('assets/picture/meodap.png');
        this.textures.info = await this.graphics.loadTexture('assets/picture/info.png');
        this.textures.diemmeo = await this.graphics.loadTexture('assets/picture/diemmeo.png');
        this.textures.diemchuot = await this.graphics.loadTexture('assets/picture/diemchuot.png');
        this.textures.huongdan = await this.graphics.loadTexture('assets/picture/huongdan.png');
        this.textures.pause = await this.graphics.loadTexture('assets/picture/pause.png');
        this.textures.menupause = await this.graphics.loadTexture('assets/picture/manhinhpause.png');
        this.textures.volumebar = await this.graphics.loadTexture('assets/picture/volumebar.png');
        this.textures.cursor = await this.graphics.loadTexture('assets/picture/cursor.png');
        this.textures.settings = await this.graphics.loadTexture('assets/picture/settings.png');
        this.textures.menuset = await this.graphics.loadTexture('assets/picture/manhinhset.png');
        this.textures.tick = await this.graphics.loadTexture('assets/picture/tick.png');
        
        // Load mouse textures
        this.textures.anhsong = [];
        this.textures.anhchet = [];
        const mouseTypes = ['xamsong', 'nausong', 'camsong', 'xanh'];
        const mouseDead = ['xamchet', 'nauchet', 'camchet', 'xanh'];
        
        for (let i = 0; i < 4; i++) {
            this.textures.anhsong[i] = await this.graphics.loadTexture(`assets/picture/${mouseTypes[i]}.png`);
            this.textures.anhchet[i] = await this.graphics.loadTexture(`assets/picture/${mouseDead[i]}.png`);
        }
        
        // Load music
        this.music.retro = await this.graphics.loadMusic('assets/sound/retroarcadesound.mp3');
        this.music.mario = await this.graphics.loadMusic('assets/sound/mario.mp3');
        this.music.bitgame = await this.graphics.loadMusic('assets/sound/bitgame.mp3');
        this.currentMusic = this.music.retro;
        
        // Load sounds
        this.sounds.hup = await this.graphics.loadSound('assets/sound/hup-sound.mpga');
        this.sounds.meow = await this.graphics.loadSound('assets/sound/meow.mp3');
        this.sounds.pop = await this.graphics.loadSound('assets/sound/pop.mp3');
        
        this.graphics.playMusic(this.currentMusic);
    }

    handleEvents(event) {
        switch (event.type) {
            case 'click':
                this.handleClick(event.offsetX, event.offsetY);
                break;
            case 'keydown':
                if (event.key === 'Escape' && this.curState === State.Playing) {
                    this.curState = State.Pause;
                }
                break;
            case 'mousedown':
                this.handleMouseDown(event.offsetX, event.offsetY);
                break;
            case 'mouseup':
                this.handleMouseUp(event.offsetX, event.offsetY);
                break;
            case 'mousemove':
                this.handleMouseMove(event.offsetX, event.offsetY);
                break;
        }
    }

    handleClick(x, y) {
        switch (this.curState) {
            case State.StartScreen:
                if (this.nutBatDau.isInside(x, y)) {
                    this.curState = State.Playing;
                    this.resetGame();
                }
                if (this.nutInfo.isInside(x, y)) {
                    this.curState = State.InfoScreen;
                }
                if (this.nutSet.isInside(x, y)) {
                    this.curState = State.Settings;
                }
                break;
                
            case State.Playing:
                this.handleGameClick(x, y);
                if (this.nutPause.isInside(x, y)) {
                    this.curState = State.Pause;
                }
                break;
                
            case State.GameOver:
                if (this.nutPlayAgain.isInside(x, y)) {
                    this.curState = State.Playing;
                    this.resetGame();
                }
                break;
                
            case State.InfoScreen:
                if (this.tatInfo.isInside(x, y)) {
                    this.curState = State.StartScreen;
                }
                break;
                
            case State.Pause:
                if (this.nutResume.isInside(x, y)) {
                    this.curState = State.Playing;
                }
                if (this.nutHome.isInside(x, y)) {
                    this.curState = State.StartScreen;
                }
                break;
                
            case State.Settings:
                this.handleSettingsClick(x, y);
                break;
        }
    }

    handleGameClick(x, y) {
        for (let i = 0; i < this.mouse.length; i++) {
            if (this.cot[this.mouse[i].col].isInside(x, y) && this.mouse[i].visible && this.mouse[i].song) {
                this.mouse[i].song = false;
                this.mouse[i].texSong = this.textures.anhchet[this.mouse[i].col];
                
                // Different mouse types give different points
                if (this.mouse[i].col === 3) { // Green mouse - game over
                    this.stat.lives = 0;
                } else {
                    this.stat.score += (this.mouse[i].col + 1);
                    this.graphics.playSound(this.sounds.pop);
                }
                break;
            }
        }
    }

    handleSettingsClick(x, y) {
        if (this.m1.isInside(x, y)) {
            this.currentMusic = this.music.retro;
            this.graphics.playMusic(this.currentMusic);
        }
        if (this.m2.isInside(x, y)) {
            this.currentMusic = this.music.mario;
            this.graphics.playMusic(this.currentMusic);
        }
        if (this.m3.isInside(x, y)) {
            this.currentMusic = this.music.bitgame;
            this.graphics.playMusic(this.currentMusic);
        }
        if (this.nutHome.isInside(x, y)) {
            this.curState = State.StartScreen;
        }
    }

    handleMouseDown(x, y) {
        if (this.curState === State.Settings) {
            if (this.vlbar.isInside(x, y)) {
                this.dragvol = true;
            }
            if (this.sfxbar.isInside(x, y)) {
                this.dragsfx = true;
            }
        }
    }

    handleMouseUp(x, y) {
        this.dragvol = false;
        this.dragsfx = false;
        this.muzik = false;
    }

    handleMouseMove(x, y) {
        if (this.dragvol && this.curState === State.Settings) {
            const tmp = Math.max(0, Math.min(272, x - 90));
            this.musicX = tmp;
            this.graphics.setMusicVolume(tmp / 272);
        }
        if (this.dragsfx && this.curState === State.Settings) {
            const tmp = Math.max(0, Math.min(272, x - 90));
            this.sfxX = tmp;
            this.graphics.setSfxVolume(tmp / 272);
        }
    }

    update() {
        const currentTime = Date.now();
        
        if (this.curState === State.Playing) {
            // Spawn mice
            if (currentTime - this.lastSpawnTime > this.spawnInterval) {
                this.spawnMouseIfNeeded();
                this.lastSpawnTime = currentTime;
                
                // Increase difficulty
                if (this.spawnInterval > 800) {
                    this.spawnInterval -= 50;
                }
            }
            
            // Update mice
            for (let i = this.mouse.length - 1; i >= 0; i--) {
                const mouse = this.mouse[i];
                mouse.y += mouse.speed;
                
                // Remove mice that went off screen
                if (mouse.y > 800) {
                    if (mouse.song && mouse.col !== 3) { // Didn't catch mouse (except green)
                        this.stat.lives--;
                        this.graphics.playSound(this.sounds.meow);
                    }
                    this.mouse.splice(i, 1);
                }
            }
            
            // Check game over
            if (this.stat.lives <= 0) {
                this.curState = State.GameOver;
                this.stat.updateHighScore();
            }
        }
    }

    spawnMouseIfNeeded() {
        const col = Math.floor(Math.random() * 4);
        const mouseType = Math.floor(Math.random() * 100);
        let type, speed;
        
        if (mouseType < 50) {
            type = 0; speed = 2; // Gray mouse
        } else if (mouseType < 80) {
            type = 1; speed = 3; // Brown mouse  
        } else if (mouseType < 95) {
            type = 2; speed = 4; // Orange mouse
        } else {
            type = 3; speed = 4; // Green mouse (deadly)
        }
        
        const newMouse = new Mouse(
            col,
            350,
            speed,
            this.textures.anhsong[type],
            this.textures.anhchet[type],
            true,
            true
        );
        
        this.mouse.push(newMouse);
    }

    render() {
        this.graphics.clear();
        
        switch (this.curState) {
            case State.StartScreen:
                this.renderStartScreen();
                break;
            case State.Playing:
                this.renderGameScreen();
                break;
            case State.GameOver:
                this.renderGameOverScreen();
                break;
            case State.InfoScreen:
                this.renderInfoScreen();
                break;
            case State.Pause:
                this.renderPauseScreen();
                break;
            case State.Settings:
                this.renderSettingsScreen();
                break;
        }
    }

    renderStartScreen() {
        this.graphics.renderTexture(this.textures.background, 0, 0);
        this.graphics.renderTexture(this.textures.play, 100, 550);
        this.graphics.renderTexture(this.textures.info, 10, 20);
        this.graphics.renderTexture(this.textures.settings, 400, 10);
        this.graphics.renderText('WHACK-A-MOUSE', 150, 100, '40px Arial', '#fff');
        this.graphics.renderText(`High Score: ${this.stat.mxscore}`, 150, 150, '20px Arial', '#fff');
    }

    renderGameScreen() {
        this.graphics.renderTexture(this.textures.background, 0, 0);
        this.graphics.renderTexture(this.textures.board, 60, 350);
        this.graphics.renderTexture(this.textures.pause, 400, 10);
        
        // Render mice
        for (const mouse of this.mouse) {
            if (mouse.visible) {
                const texture = mouse.song ? mouse.texSong : mouse.texChet;
                const x = this.xBasechuot[mouse.col];
                this.graphics.renderTexture(texture, x, mouse.y, 50, 50);
            }
        }
        
        // Render UI
        this.graphics.renderText(`Score: ${this.stat.score}`, 20, 30, '20px Arial', '#fff');
        this.graphics.renderText(`Lives: ${this.stat.lives}`, 20, 60, '20px Arial', '#fff');
    }

    renderGameOverScreen() {
        this.graphics.renderTexture(this.textures.background, 0, 0);
        this.graphics.renderText('GAME OVER', 150, 200, '40px Arial', '#fff');
        this.graphics.renderText(`Final Score: ${this.stat.score}`, 150, 250, '24px Arial', '#fff');
        this.graphics.renderText(`High Score: ${this.stat.mxscore}`, 150, 280, '24px Arial', '#fff');
        this.graphics.renderTexture(this.textures.playagain, 100, 550);
    }

    renderInfoScreen() {
        this.graphics.renderTexture(this.textures.huongdan, 0, 0);
        this.graphics.renderTexture(this.textures.diemchuot, 360, 200);
        this.graphics.renderTexture(this.textures.diemmeo, 360, 200);
    }

    renderPauseScreen() {
        this.graphics.renderTexture(this.textures.menupause, 0, 0);
    }

    renderSettingsScreen() {
        this.graphics.renderTexture(this.textures.menuset, 0, 0);
        this.graphics.renderTexture(this.textures.volumebar, 90, 280);
        this.graphics.renderTexture(this.textures.volumebar, 90, 390);
        
        // Volume sliders
        const volX = Math.min(342, Math.max(90, 90 + this.musicX - 10));
        const sfxVolX = Math.min(342, Math.max(90, 90 + this.sfxX - 10));
        this.graphics.renderTexture(this.textures.cursor, volX, 280);
        this.graphics.renderTexture(this.textures.cursor, sfxVolX, 390);
        
        // Music options
        this.graphics.renderTexture(this.textures.tick, 150, 500);
    }

    resetGame() {
        this.stat.resetGame();
        this.mouse = [];
        this.spawnInterval = 2000;
        this.lastSpawnTime = Date.now();
    }

    run() {
        const gameLoop = () => {
            if (this.isRunning) {
                this.update();
                this.render();
                requestAnimationFrame(gameLoop);
            }
        };
        
        // Start game loop
        requestAnimationFrame(gameLoop);
        
        // Set up event listeners
        this.graphics.canvas.addEventListener('click', (e) => this.handleEvents({type: 'click', offsetX: e.offsetX, offsetY: e.offsetY}));
        this.graphics.canvas.addEventListener('mousedown', (e) => this.handleEvents({type: 'mousedown', offsetX: e.offsetX, offsetY: e.offsetY}));
        this.graphics.canvas.addEventListener('mouseup', (e) => this.handleEvents({type: 'mouseup', offsetX: e.offsetX, offsetY: e.offsetY}));
        this.graphics.canvas.addEventListener('mousemove', (e) => this.handleEvents({type: 'mousemove', offsetX: e.offsetX, offsetY: e.offsetY}));
        document.addEventListener('keydown', (e) => this.handleEvents({type: 'keydown', key: e.key}));
    }
}