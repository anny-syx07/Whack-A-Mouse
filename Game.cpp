#include "Game.h"
#include "Graphics.h"

bool dragvol=false;
bool dragsfx=false;
float musicvol=80;
float sfxvol=80;
bool muzik=false;

void Game::init() {
    srand(time(0));
    graphics.init();

    gMusic1 = graphics.loadMusic("assets/sound/retroarcadesound.mp3");
    gMusic=gMusic1;
    graphics.toggle(gMusic1);

    gMusic2=graphics.loadMusic("assets/sound/mario.mp3");
    gMusic3=graphics.loadMusic("assets/sound/bitgame.mp3");

    hup = graphics.loadChunk("assets/sound/hup-sound.mpga");
    meow = graphics.loadChunk("assets/sound/meow.mp3");
    pop = graphics.loadChunk("assets/sound/pop.mp3");

    background = graphics.loadTexture("assets/picture/background.jpg");
    playTexture = graphics.loadTexture("assets/picture/play.png");
    playagain = graphics.loadTexture("assets/picture/playagain.png");
    boardTexture = graphics.loadTexture("assets/picture/board.png");
    meodungyen = graphics.loadTexture("assets/picture/meodungyen.png");
    meodap = graphics.loadTexture("assets/picture/meodap.png");
    info = graphics.loadTexture("assets/picture/info.png");
    diemmeo = graphics.loadTexture("assets/picture/diemmeo.png");
    diemchuot = graphics.loadTexture("assets/picture/diemchuot.png");
    huongdan = graphics.loadTexture("assets/picture/huongdan.png");
    pausebutton=graphics.loadTexture("assets/picture/pause.png");
    menupause=graphics.loadTexture("assets/picture/manhinhpause.png");
    volumebar=graphics.loadTexture("assets/picture/volumebar.png");
    cursorvl=graphics.loadTexture("assets/picture/cursor.png");
    cursorsfx=cursorvl;
    sets=graphics.loadTexture("assets/picture/settings.png");
    menuset=graphics.loadTexture("assets/picture/manhinhset.png");
    tick=graphics.loadTexture("assets/picture/tick.png");

    for (int i = 0; i < 4; ++i) {
        anhsong[i] = graphics.loadTexture(("assets/picture/" + std::string(i == 0 ? "xamsong" : i == 1 ? "nausong" : i==2?"camsong":"xanh") + ".png").c_str());
        anhchet[i] = graphics.loadTexture(("assets/picture/" + std::string(i == 0 ? "xamchet" : i == 1 ? "nauchet" : i==2?"camchet":"xanh") + ".png").c_str());
    }

    xBasechuot[0] = 110; xBasechuot[1] = 170; xBasechuot[2] = 250; xBasechuot[3] = 320;
    xBasemeo[0] = 80;  xBasemeo[1] = 150; xBasemeo[2] = 220; xBasemeo[3] = 300;

    welcome = graphics.loadFont("assets/font/fluff.ttf", 100);
    gover = graphics.loadFont("assets/font/fluff.ttf", 80);
    diem = graphics.loadFont("assets/font/diem.ttf", 30);
    ingame = graphics.loadFont("assets/font/shortbaby.ttf", 20);
    opt=graphics.loadFont("assets/font/fluff.ttf",20);

    hello = graphics.renderText("Whack a", welcome, color);
    hellodongduoi = graphics.renderText("mouse!", welcome, color);
    gameover = graphics.renderText("Game over", gover, color);
    yourscore = graphics.renderText("Your score: ", diem, diemm);
    highscore = graphics.renderText("High score: ", diem, diemm);
    volume=graphics.renderText("Volume ",diem,diemm);
    sfx=graphics.renderText("Sound effect ",diem,diemm);
    mzopt=graphics.renderText("Music",diem,diemm);
    option=graphics.renderText("Retro         Mario        Bitgame",opt,{0,0,0,0});

    stat.loadHighScore();
}

void Game::updateSlider(){
    if(dragvol){
        float tmp=std::max(0,std::min(272,x-90));
        musicvol=tmp*128/272;
        Mix_VolumeMusic(musicvol);
    }
    int musicX=musicvol*272/128;
    graphics.renderTexture(cursorvl,std::min(342,std::max(90,90+musicX-10)),280);

    if(dragsfx){
        float tmp=std::max(0,std::min(272,x-90));
        sfxvol=tmp*128/272;
        Mix_Volume(-1,sfxvol);
    }
    int sfxX=sfxvol*272/128;
    graphics.renderTexture(cursorsfx,std::min(342,std::max(90,90+sfxX-10)),390);

}

void Game::updateMusic(){
    if(muzik){
        graphics.toggle(gMusic);
        if(m1.checkmouse(x,y)){
            graphics.renderTexture(tick,180,500);
            gMusic=gMusic1;
        }
        else if(m2.checkmouse(x,y)){
            graphics.renderTexture(tick,250,500);
            gMusic=gMusic2;
        }
        else if(m3.checkmouse(x,y)){
            graphics.renderTexture(tick,380,500);
            gMusic=gMusic3;
        }
        graphics.toggle(gMusic);
    }
    if(gMusic==gMusic1){
        graphics.renderTexture(tick,150,500);
    }
    if(gMusic==gMusic2){
        graphics.renderTexture(tick,250,500);
    }
    if(gMusic==gMusic3){
        graphics.renderTexture(tick,380,500);
    }
}

void Game::run() {
    init();
    bool isRunning = true;

    while (isRunning) {
        graphics.prepareScene(background);
        handleEvents();
        update();
        graphics.presentScene();
    }

    cleanUp();
}

void Game::handleEvents() {
    SDL_GetMouseState(&x, &y);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            cleanUp();
            exit(0);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {

            if (nutBatDau.checkmouse(x, y) && curState == State::StartScreen) {
                stat.reset();
                resetGame();
                curState = State::Playing;

            } else if(nutSet.checkmouse(x,y)&&curState==State::StartScreen){
                curState=State::Settings;
            }
            else if(curState==State::Settings){
                if(nutHome.checkmouse(x,y))
                    curState=State::StartScreen;
                else if(vlbar.checkmouse(x,y)) dragvol=true;
                else if(sfxbar.checkmouse(x,y)) dragsfx=true;
                else if(m1.checkmouse(x,y)||m2.checkmouse(x,y)||m3.checkmouse(x,y)){
                    muzik=true;
                }
            }

            else if (nutInfo.checkmouse(x, y) && curState == State::StartScreen) {
                curState = State::InfoScreen;
            } else if (tatInfo.checkmouse(x, y) && curState == State::InfoScreen) {
                curState = State::StartScreen;
            } else if (nutPlayAgain.checkmouse(x, y) && curState == State::GameOver) {
                stat.reset();
                resetGame();
                curState = State::Playing;

            } else if(curState==State::Playing)
            {
                for(int i=0;i<4;i++){
                    if(cot[i].checkmouse(x,y)){
                        cot[i].click=true;
                        cot[i].firsttime=true;
                        cot[i].clickTime = SDL_GetTicks();
                        cot[i].playingAnimation = true;
                        for(int j=0;j<4;j++){
                            if(i!=j){
                                cot[j].click=false;
                            }
                        }
                    }
                }
                if(nutPause.checkmouse(x,y)){
                    curState=State::Pause;
                }
            } else if(curState==State::Pause){
                if(nutHome.checkmouse(x,y))
                    curState=State::StartScreen;
                else if(nutResume.checkmouse(x,y)){
                    curState=State::Playing;
                }
                else if(vlbar.checkmouse(x,y)) dragvol=true;
                else if(sfxbar.checkmouse(x,y)) dragsfx=true;
            }
        }
        if(event.type==SDL_MOUSEBUTTONUP){
            dragvol=false;
            dragsfx=false;
            muzik=false;
        }
        if(event.type==SDL_KEYDOWN&&curState==State::Playing){
            if(event.key.keysym.sym==SDLK_ESCAPE){
                curState=State::Pause;
            }
        }
    }
}

void Game::resetGame() {
    mouse.clear();
    for (int i = 0; i < 4; ++i) {
        cot[i].click = false;
        cot[i].firsttime = true;
        cot[i].playingAnimation = false;
    }
    newGame=0;
    clicked = false;
    spawnInterval=3000;
}


void Game::update() {
    switch (curState) {
        case State::StartScreen:
            graphics.renderTexture(info, 10, 20);
            graphics.renderTexture(playTexture, 100, 550);
            graphics.renderTexture(hello, 20, 200);
            graphics.renderTexture(hellodongduoi, 80, 350);
            graphics.renderTexture(sets,400,10);
            break;

        case State::InfoScreen:
            graphics.renderTexture(huongdan, 60, 200);
            break;

        case State::Settings:
            graphics.renderTexture(menuset,60,200);
            graphics.renderTexture(volume,70,220);
            graphics.renderTexture(sfx,70,330);
            graphics.renderTexture(volumebar,90,280);
            graphics.renderTexture(volumebar,90,390);
            graphics.renderTexture(mzopt,70,440);
            graphics.renderTexture(option,70,500);
            updateMusic();
            updateSlider();
            break;

        case State::GameOver: {
            SDL_Texture* scoree = graphics.renderText(std::to_string(stat.score).c_str(), ingame, baby);
            SDL_Texture* mangg = graphics.renderText(std::to_string(stat.lives).c_str(), ingame, baby);
            SDL_Texture* hiscoree = graphics.renderText(std::to_string(stat.getHighScore()).c_str(), ingame, baby);

            graphics.renderTexture(playagain, 180, 550);
            graphics.renderTexture(gameover, 10, 200);
            graphics.renderTexture(yourscore, 100, 300);
            graphics.renderTexture(scoree, 300, 310);
            graphics.renderTexture(highscore, 100, 350);
            graphics.renderTexture(hiscoree, 300, 360);
            break;
        }

        case State::Playing: {
            if(stat.score>=30) spawnInterval=1500;
            else if(stat.score>=50) spawnInterval=1000;
            else if(stat.score>=80) spawnInterval=500;
            else if(stat.score>=100) spawnInterval=200;
            if(!newGame) {mouse.clear(); clicked=false;}
            graphics.renderTexture(diemmeo, 2, 50);
            graphics.renderTexture(diemchuot, 2, 10);
            graphics.renderTexture(graphics.renderText(std::to_string(stat.score).c_str(), ingame, baby), 60, 20);
            graphics.renderTexture(graphics.renderText(std::to_string(stat.lives).c_str(), ingame, baby), 60, 60);
            graphics.renderTexture(boardTexture, 0, 350);
            graphics.renderTexture(pausebutton,400,10);
            for (int i = 0; i < 4; i++) {
                if (cot[i].click) {
                    newGame++;
                    Uint32 currentTime = SDL_GetTicks();
                    if (cot[i].playingAnimation && currentTime - cot[i].clickTime <= 200) {
        // Hiện mèo đập trong 200ms
                        graphics.renderTexture(meodap, xBasemeo[i], 260);
                        if (cot[i].firsttime) {
                            Mix_PlayChannel(-1, hup, 0);
                            cot[i].firsttime = false;
                        }
                        for (auto& c : mouse) {
                            if (c.song && c.col == i && c.y <= 330&&c.y>=310) {
                                c.song=false;
                                if(c.speed==4) curState=State::GameOver;
                            }
                        }
                    } else {
        // Sau 200ms hiện mèo đứng yên
                        graphics.renderTexture(meodungyen, xBasemeo[i], 250);
                        cot[i].playingAnimation = false;
                    }
                    clicked=true;
                }
            }
            if(!clicked){
                graphics.renderTexture(meodungyen,190,250);
            }

            if (SDL_GetTicks() - lastSpawnTime >= spawnInterval) {
                int col = rand() % 4;
                int type;
                if(stat.score<30) type = rand() % 3;
                else type=rand()%4;
                Mouse c(col, 800, type + 1, anhsong[type], anhchet[type], true, true);
                mouse.push_back(c);
                lastSpawnTime = SDL_GetTicks();
            }



            for (auto& c : mouse) {
                if (c.visible) {
                    c.y -= c.speed;
                    if (c.y <= 300) {
                        c.visible = false;
                        if (c.song) {
                            if(c.speed!=4){
                                stat.loseLife();
                                Mix_PlayChannel(-1, meow, 0);
                            }
                        } else {
                            stat.addScore(c.speed);
                            Mix_PlayChannel(-1, pop, 0);
                        }
                    }
                }
            }


            for (auto& c : mouse) {
                if (!c.visible) continue;
                if (c.song)
                    graphics.renderTexture(c.texsong, xBasechuot[c.col], c.y);
                else
                    graphics.renderTexture(c.texchet, xBasechuot[c.col], c.y);
            }
            if(stat.lives<=0) {curState=State::GameOver;};
            break;
        }
        case State::Pause:
            graphics.renderTexture(menupause,60,200);
            graphics.renderTexture(volume,70,220);
            graphics.renderTexture(sfx,70,330);
            graphics.renderTexture(volumebar,90,280);
            graphics.renderTexture(volumebar,90,390);
            updateSlider();
            break;

    }
}

void Game::cleanUp() {
    stat.saveHighScore();
    graphics.quit();
}

