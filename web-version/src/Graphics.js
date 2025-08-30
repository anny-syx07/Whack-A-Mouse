export class Graphics {
    constructor(canvas) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        this.images = new Map();
        this.sounds = new Map();
        this.music = new Map();
        this.currentMusic = null;
        this.musicVolume = 0.5;
        this.sfxVolume = 0.5;
    }

    async loadTexture(path) {
        if (this.images.has(path)) {
            return this.images.get(path);
        }
        
        return new Promise((resolve, reject) => {
            const img = new Image();
            img.onload = () => {
                this.images.set(path, img);
                resolve(img);
            };
            img.onerror = reject;
            img.src = path;
        });
    }

    async loadMusic(path) {
        if (this.music.has(path)) {
            return this.music.get(path);
        }

        const audio = new Audio(path);
        audio.loop = true;
        audio.volume = this.musicVolume;
        this.music.set(path, audio);
        return audio;
    }

    async loadSound(path) {
        if (this.sounds.has(path)) {
            return this.sounds.get(path);
        }

        const audio = new Audio(path);
        audio.volume = this.sfxVolume;
        this.sounds.set(path, audio);
        return audio;
    }

    renderTexture(image, x, y, width = null, height = null) {
        if (!image) return;
        
        const w = width || image.width;
        const h = height || image.height;
        this.ctx.drawImage(image, x, y, w, h);
    }

    renderText(text, x, y, font = '20px Arial', color = '#fff') {
        this.ctx.font = font;
        this.ctx.fillStyle = color;
        this.ctx.fillText(text, x, y);
    }

    clear() {
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }

    playMusic(audio) {
        if (this.currentMusic) {
            this.currentMusic.pause();
            this.currentMusic.currentTime = 0;
        }
        this.currentMusic = audio;
        audio.play().catch(e => console.log('Music play failed:', e));
    }

    playSound(audio) {
        if (audio) {
            audio.currentTime = 0;
            audio.play().catch(e => console.log('Sound play failed:', e));
        }
    }

    setMusicVolume(volume) {
        this.musicVolume = volume;
        if (this.currentMusic) {
            this.currentMusic.volume = volume;
        }
    }

    setSfxVolume(volume) {
        this.sfxVolume = volume;
        this.sounds.forEach(sound => {
            sound.volume = volume;
        });
    }
}