import numpy as np
import pygame

import PyGameBoard as GameBoard

from pygame.locals import (
    K_ESCAPE,
    KEYDOWN,
    QUIT,
    MOUSEBUTTONDOWN,
)


# Initialize pygame
pygame.init()
clock = pygame.time.Clock()

# Define constants for the screen width and height

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800
BOARD_BUFFER_X = 25
BOARD_BUFFER_Y = 25


HUMAN_PLAY_AS_O = True
DEPTH1 = 2
DEPTH2 = 4

DEPTHS = [3, 4, 6, 8, 10]
TIME_LIMIT = 4

SIMS = 100000
SIMS_PER_FRAME = 20000
SIMS_CHUNK_SIZE = SIMS


def draw_game(screen, game):

    draw_board(screen)

    board_index = -1
    for miniboard in range(9):
        board_index += 1

        miniboard_status = game.checkMiniboard(miniboard)

        board_x = board_index % 3
        board_y = int(board_index / 3)

        if miniboard_status != 0:

            board_start_x = (
                SCREEN_WIDTH - 2 * BOARD_BUFFER_X
            ) / 3 * board_x + BOARD_BUFFER_X

            board_start_y = (
                SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y
            ) / 3 * board_y + BOARD_BUFFER_Y

            if miniboard_status == 1:
                img = big_font.render("X", True, (200, 100, 100))

            elif miniboard_status == 2:
                img = big_font.render("O", True, (100, 100, 200))

            else:
                img = big_font.render("T", True, (100, 100, 100))

            board_width = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 3

            board_height = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 3

            imgx = board_start_x + 0.5 * board_width - 0.5 * img.get_width()
            imgy = board_start_y + 0.5 * board_height - 0.5 * img.get_height()

            screen.blit(img, (imgx, imgy))
        else:
            for spot_index in range(miniboard * 9, miniboard * 9 + 9):

                if game.getSpot(spot_index) == 1:
                    draw_move(screen, spot_index // 9, spot_index % 9, "X", font)

                elif game.getSpot(spot_index) == 2:
                    draw_move(screen, spot_index // 9, spot_index % 9, "O", font)

    if game.getRequiredBoard() != -1:
        if not game.x_to_move:
            box_board(screen, game.getRequiredBoard(), (100, 100, 200))
        else:
            box_board(screen, game.getRequiredBoard(), (200, 100, 100))

    else:
        if not game.x_to_move:
            to_move_color = (100, 100, 200)
        else:
            to_move_color = (200, 100, 100)
        pygame.draw.rect(
            screen,
            to_move_color,
            pygame.Rect(
                BOARD_BUFFER_X,
                BOARD_BUFFER_Y,
                SCREEN_WIDTH - 2 * BOARD_BUFFER_X,
                SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y,
            ),
            width=5,
        )

    pygame.display.flip()


def box_board(screen, board_index, to_move_color):
    board_x = board_index % 3
    board_y = int(board_index / 3)

    board_start_x = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 3 * board_x + BOARD_BUFFER_X

    board_start_y = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 3 * board_y + BOARD_BUFFER_Y

    board_width = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 3

    board_height = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 3

    pygame.draw.rect(
        screen,
        to_move_color,
        pygame.Rect(board_start_x, board_start_y, board_width, board_height),
        width=5,
    )


def draw_board(screen):
    for i in range(1, 3):
        line_x = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 3 * i + BOARD_BUFFER_X

        pygame.draw.line(
            screen,
            (0, 0, 0),
            (line_x, BOARD_BUFFER_Y),
            (line_x, SCREEN_HEIGHT - BOARD_BUFFER_Y),
            width=5,
        )

    for i in range(1, 3):
        line_y = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 3 * i + BOARD_BUFFER_Y

        pygame.draw.line(
            screen,
            (0, 0, 0),
            (BOARD_BUFFER_X, line_y),
            (SCREEN_WIDTH - BOARD_BUFFER_X, line_y),
            width=5,
        )

    line_width = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X / 3) / 3

    line_height = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y / 3) / 3

    # Draw the small boards
    for board_pos_x in range(3):

        for board_pos_y in range(3):

            board_start_x = (
                SCREEN_WIDTH - 2 * BOARD_BUFFER_X
            ) / 3 * board_pos_x + BOARD_BUFFER_X

            board_start_y = (
                SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y
            ) / 3 * board_pos_y + BOARD_BUFFER_Y

            for line_number in range(1, 3):
                line_x = (
                    board_start_x
                    + (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 9 * line_number
                )

                line_y = (
                    board_start_y
                    + (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 9 * line_number
                )

                pygame.draw.line(
                    screen,
                    (0, 0, 0),
                    (line_x, board_start_y + BOARD_BUFFER_Y),
                    (line_x, board_start_y + line_height - BOARD_BUFFER_Y),
                )

                pygame.draw.line(
                    screen,
                    (0, 0, 0),
                    (board_start_x + BOARD_BUFFER_X, line_y),
                    (board_start_x + line_width - BOARD_BUFFER_X, line_y),
                )


def mouse_pos_to_board_and_piece(mouse_pos):
    x_coord = int(
        ((mouse_pos[0] - BOARD_BUFFER_X) / ((SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 9))
    )
    y_coord = int(
        ((mouse_pos[1] - BOARD_BUFFER_Y) / ((SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 9))
    )

    print(x_coord)
    print(y_coord)

    return absolute_coords_to_board_and_piece(x_coord, y_coord)


def absolute_coords_to_board_and_piece(xpos, ypos):

    # i = index
    # gx = global x value (independent of board)
    # gy = same
    #
    # lx = local x value (within board)
    # ly = same
    #
    # bx = x value of the whole board
    # by = same
    #
    # pi = piece index
    # bi = board index

    i = xpos + 9 * ypos

    gx = i % 9
    gy = int(i / 9)

    lx = gx % 3
    ly = gy % 3

    bx = int((i % 9) / 3)
    by = int(i / 27)

    pi = ly * 3 + lx
    bi = by * 3 + bx

    return bi, pi


def draw_move(screen, board, piece, text, font, color=None):
    board_x = board % 3
    board_y = int(board / 3)

    piece_x = piece % 3
    piece_y = int(piece / 3)

    board_start_x = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 3 * board_x + BOARD_BUFFER_X

    board_start_y = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 3 * board_y + BOARD_BUFFER_Y

    board_width = (SCREEN_WIDTH - 2 * BOARD_BUFFER_X) / 3

    board_height = (SCREEN_HEIGHT - 2 * BOARD_BUFFER_Y) / 3

    piece_start_x = (
        board_start_x
        + BOARD_BUFFER_X
        + (board_width - 2 * BOARD_BUFFER_X) / 3 * piece_x
    )
    piece_start_y = (
        board_start_y
        + BOARD_BUFFER_Y
        + (board_height - 2 * BOARD_BUFFER_Y) / 3 * piece_y
    )

    if color is not None:
        img = font.render(text, True, color)

    else:
        if text == "O":

            img = font.render(text, True, (100, 100, 200))
        elif text == "X":
            img = font.render(text, True, (200, 100, 100))

        else:
            img = font.render(text, True, (0, 0, 0))

    draw_x = piece_start_x + 0.5 * (board_width / 3) - 0.5 * img.get_width()
    draw_y = piece_start_y + 0.5 * (board_height / 3) - 0.5 * img.get_height()

    screen.blit(img, (draw_x, draw_y))


def display_message(screen, text, color=(255, 255, 255), bg_color=(100, 100, 100)):
    img = med_font.render(text, True, color)

    rectx = SCREEN_WIDTH / 2 - img.get_width() / 2 - 10
    recty = SCREEN_HEIGHT / 2 - img.get_height() / 2 - 10

    width = img.get_width() + 20
    height = img.get_height() + 20

    # Draw the background
    pygame.draw.rect(
        screen, bg_color, pygame.Rect(rectx, recty, width, height),
    )

    # Draw the text
    screen.blit(img, (rectx + 10, recty + 10))
    pygame.display.flip()


if __name__ == "__main__":
    pygame.init()

    # Create the screen object

    # The size is determined by the constant SCREEN_WIDTH and SCREEN_HEIGHT

    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

    running = True

    screen.fill((255, 255, 255))

    draw_board(screen)

    font = pygame.font.SysFont(None, 65)

    big_font = pygame.font.SysFont(None, 425)
    med_font = pygame.font.SysFont(None, 200)

    game = GameBoard.PyMCTS()

    if HUMAN_PLAY_AS_O:
        game.runSimulations(SIMS)
        game.makeBestMove()

    draw_game(screen, game)
    is_players_move = True
    game_running = True

    sims_complete = 0

    while running:

        clock.tick(30)

        if game_running:
            screen.fill((255, 255, 255))
            draw_game(screen, game)

        if not is_players_move and game_running:
            pygame.event.pump()
            game.runSimulations(SIMS_CHUNK_SIZE)

            sims_complete += SIMS_CHUNK_SIZE

            if sims_complete >= SIMS:
                game.makeBestMove()
                sims_complete = 0

                is_players_move = True

                result = game.getGameStatus()

                if result != 0:
                    screen.fill((255, 255, 255))
                    draw_game(screen, game)
                    if result == 1:
                        display_message(screen, "X WINS!")
                    elif result == 2:
                        display_message(screen, "O WINS!")
                    elif result == -1:
                        display_message(screen, "TIE GAME!")

                    game_running = False
                    is_players_move = False
                    continue

        elif is_players_move and game_running:
            game.runSimulations(SIMS_PER_FRAME)

            for event in pygame.event.get():
                # Did the user hit a key?

                if event.type == KEYDOWN:

                    # Was it the Escape key? If so, stop the loop.

                    if event.key == K_ESCAPE:
                        running = False

                # Did the user click the window close button? If so, stop the loop.

                elif event.type == QUIT:

                    running = False

                elif event.type == MOUSEBUTTONDOWN and is_players_move and game_running:
                    is_players_move = False
                    board, piece = mouse_pos_to_board_and_piece(pygame.mouse.get_pos())

                    if not game.validMove(board * 9 + piece):
                        print(
                            "Your move was not found as a valid move. Are you sure you entered it correctly?"
                        )
                        is_players_move = True
                        continue

                    game.makeMove(board * 9 + piece)

                    game.display()

                    result = game.getGameStatus()

                    if result != 0:
                        screen.fill((255, 255, 255))
                        draw_game(screen, game)
                        if result == 1:
                            display_message(screen, "X WINS!")
                        elif result == 2:
                            display_message(screen, "O WINS!")
                        elif result == -1:
                            display_message(screen, "TIE GAME!")

                        game_running = False
                        continue

        else:
            pygame.event.pump()
