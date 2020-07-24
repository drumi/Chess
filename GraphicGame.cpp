#include "GraphicGame.h"
#include "TextureLoader.h"
#include "ChessAI.h"
#include <iostream>

namespace {
    char const* chess_board = "chess_board";
    char const* white_king = "white_king";
    char const* black_king = "black_king";
    char const* white_rook = "white_rook";
    char const* black_rook = "black_rook";
    char const* white_pawn = "white_pawn";
    char const* black_pawn = "black_pawn";
    char const* white_knight = "white_knight";
    char const* black_knight = "black_knight";
    char const* white_queen = "white_queen";
    char const* black_queen = "black_queen";
    char const* white_bishop = "white_bishop";
    char const* black_bishop = "black_bishop";
    char const* checkmate = "checkmate";
    char const* stalemate = "stalemate";
}

GraphicGame::GraphicGame(int x, int y, int w, bool usingAI, int AIDepth)
:m_isRunning(true), BORDER_PIXEL_OFFSET(w / 23), SQUARE_SIZE((w - 2 * BORDER_PIXEL_OFFSET)/8), m_usingAI(usingAI), m_gameState(GameState::NORMAL), m_AIDepth(AIDepth)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = SDL_CreateWindow("Chess", x, y, w, w, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    loadTextures();
}

GraphicGame::~GraphicGame()
{
    for(auto& p : textures)
        SDL_DestroyTexture(p.second);

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void GraphicGame::loadTextures()
{
    textures[chess_board] = TextureLoader::Load(m_renderer, "Assets/chessboard.bmp");
    textures[white_king] = TextureLoader::Load(m_renderer, "Assets/Chess_klt60.bmp");
    textures[black_king] = TextureLoader::Load(m_renderer, "Assets/Chess_kdt60.bmp");
    textures[white_rook] = TextureLoader::Load(m_renderer, "Assets/Chess_rlt60.bmp");
    textures[black_rook] = TextureLoader::Load(m_renderer, "Assets/Chess_rdt60.bmp");
    textures[white_pawn] = TextureLoader::Load(m_renderer, "Assets/Chess_plt60.bmp");
    textures[black_pawn] = TextureLoader::Load(m_renderer, "Assets/Chess_pdt60.bmp");
    textures[white_queen] = TextureLoader::Load(m_renderer, "Assets/Chess_qlt60.bmp");
    textures[black_queen] = TextureLoader::Load(m_renderer, "Assets/Chess_qdt60.bmp");
    textures[white_knight] = TextureLoader::Load(m_renderer, "Assets/Chess_nlt60.bmp");
    textures[black_knight] = TextureLoader::Load(m_renderer, "Assets/Chess_ndt60.bmp");
    textures[white_bishop] = TextureLoader::Load(m_renderer, "Assets/Chess_blt60.bmp");
    textures[black_bishop] = TextureLoader::Load(m_renderer, "Assets/Chess_bdt60.bmp");
    textures[stalemate] = TextureLoader::Load(m_renderer, "Assets/stalemate.bmp");
    textures[checkmate] = TextureLoader::Load(m_renderer, "Assets/checkmate.bmp");
}

void GraphicGame::render()
{  
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, textures[chess_board], NULL, NULL);

    boardArrPtr ptr = m_game.getBoard().getPieces();

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Piece const &p = (*ptr)[y][x];
            SDL_Rect rect;
            rect.x = x * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
            rect.y = y * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
            rect.h = SQUARE_SIZE;
            rect.w = SQUARE_SIZE;

            switch (p.getType())
            {
            case PieceType::PAWN:
                if(p.isWhite())
                    SDL_RenderCopy(m_renderer, textures[white_pawn], NULL, &rect);
                else
                    SDL_RenderCopy(m_renderer, textures[black_pawn], NULL, &rect);
                break;
            
            case PieceType::KING:
                if(p.isWhite())
                    SDL_RenderCopy(m_renderer, textures[white_king], NULL, &rect);
                else
                    SDL_RenderCopy(m_renderer, textures[black_king], NULL, &rect);
                break;

            case PieceType::QUEEN:
                if(p.isWhite())
                    SDL_RenderCopy(m_renderer, textures[white_queen], NULL, &rect);
                else
                    SDL_RenderCopy(m_renderer, textures[black_queen], NULL, &rect);
                break;

            case PieceType::BISHOP:
                if(p.isWhite())
                    SDL_RenderCopy(m_renderer, textures[white_bishop], NULL, &rect);
                else
                    SDL_RenderCopy(m_renderer, textures[black_bishop], NULL, &rect);
                break;

            case PieceType::KNIGHT:
                if(p.isWhite())
                    SDL_RenderCopy(m_renderer, textures[white_knight], NULL, &rect);
                else
                    SDL_RenderCopy(m_renderer, textures[black_knight], NULL, &rect);
                break;

            case PieceType::ROOK:
                if(p.isWhite())
                    SDL_RenderCopy(m_renderer, textures[white_rook], NULL, &rect);
                else
                    SDL_RenderCopy(m_renderer, textures[black_rook], NULL, &rect);
                break;

            default:
                break;
            }
        
        }
    }

    if(m_gameState == GameState::CHECKMATE)
    {
        SDL_Rect rect;
        rect.x = 2 * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
        rect.y = 2 * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
        rect.h = 4 * SQUARE_SIZE;
        rect.w = 4 * SQUARE_SIZE;
        SDL_RenderCopy(m_renderer, textures[checkmate], NULL, &rect);
    }
    else if (m_gameState == GameState::STALEMATE)
    {
        SDL_Rect rect;
        rect.x = 2 * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
        rect.y = 2 * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
        rect.h = 4 * SQUARE_SIZE;
        rect.w = 4 * SQUARE_SIZE;
        SDL_RenderCopy(m_renderer, textures[stalemate], NULL, &rect);
    }

    if(m_nextMove.hasSource)
    {
        SDL_Rect rect;
        rect.x = m_nextMove.x * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
        rect.y = m_nextMove.y * SQUARE_SIZE + BORDER_PIXEL_OFFSET;
        rect.h = SQUARE_SIZE;
        rect.w = SQUARE_SIZE;

        if(m_game.isWhiteTurn())
        {
            SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(m_renderer, &rect);
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        }
        else
        {
            SDL_RenderDrawRect(m_renderer, &rect);
        }
        
    }

    SDL_RenderPresent(m_renderer);
}

void GraphicGame::handleEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                int x, y;
                x = (event.button.x - BORDER_PIXEL_OFFSET) / SQUARE_SIZE;
                y = (event.button.y - BORDER_PIXEL_OFFSET) / SQUARE_SIZE;
                
                if(x < 8 && y < 8)
                {
                    if(m_nextMove.hasSource)
                    {
                        m_nextMove.destx = x;
                        m_nextMove.desty = y;
                        move(m_nextMove);
                    }
                    else
                    {
                        m_nextMove.x = x;
                        m_nextMove.y = y;
                        m_nextMove.hasSource = true;
                    }
                }
            }
            else if(event.button.button == SDL_BUTTON_RIGHT)
            {
                m_gameState = GameState::NORMAL;
                if(m_usingAI)
                    m_game.undoMoveTillWhite();
                else
                    m_game.undoMove();

                m_nextMove.hasSource = false;
            }
            else if(event.button.button == SDL_BUTTON_MIDDLE)
            {
                m_gameState = GameState::NORMAL;
                m_nextMove.hasSource = false;
                m_game.restart();
            }
        
        default:
            break;
        }
    }
}

void GraphicGame::move(Move& m)
{
    m.hasSource = false;

    if(checkGameOver())
        return;

    bool successfulMove = m_game.tryMove(m.x, m.y, m.destx, m.desty);

    if(successfulMove && m_usingAI)
        moveAI();
        
}

void GraphicGame::moveAI()
{
    if(checkGameOver())
        return;

    MoveResult r = ChessAI::GetMove(m_game.getBoard(), false, m_AIDepth);
    m_game.tryMove(r.x, r.y, r.xdest, r.ydest);
}

bool GraphicGame::checkGameOver()
{
    int size = MoveGenerator::Generate(m_game.getBoard(), m_game.isWhiteTurn()).size(); // Ignoring En passant for now

    if(size == 0)
    {
        if(MoveValidator::isKingUnderCheck(m_game.getBoard(), m_game.isWhiteTurn()))
        {
            m_gameState = GameState::CHECKMATE;
        }
        else
        {
            m_gameState = GameState::STALEMATE;
        }
        return true;
    } 
    
    return false;
}