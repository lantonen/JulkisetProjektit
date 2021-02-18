#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <random>
#include <QGraphicsItem>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    std::vector<QGraphicsRectItem*> shape_;
    QGraphicsRectItem* rectangle_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Constants for move directions
    const std::string LEFT = "left";
    const std::string RIGHT = "right";
    const std::string DOWN = "down";
    const std::string UP = "up";

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;


    // For timer
    QTimer* timer_;

    // More constants, attibutes, and methods
    int score_ = 0;
    bool horizontal_up_ = false;
    bool first_rotation_ = true;
    int chosen_shape_;
    int speed_;

    // Helper methods for building shapes and moving it

    /**
     * @brief building basic element(one small square)
     * @param x coordinate
     * @param y coordinate
     * @param brush_color, makes color management easier
     * @param pen_color, if no pen color given its black
     * @return rectangle item
     */
    QGraphicsRectItem* make_small_square(int x, int y ,QColor brush_color, QColor pen_color = Qt::black);

    /**
     * @brief makes horizontal shape
     * @param amount of squares in horizontal shape
     * @param brush_color, makes color management easier
     * @param y coordinate, if not given y is 0
     * @return vector that contains rectangle items
     */
    std::vector<QGraphicsRectItem*> make_horizontal(int amount, QColor brush_color, int y = 0);

    /**
     * @brief moves shape location
     * @param direction where shape is moving
     * @param moving_shape, shape that needs to be moved
     */
    void move_it(std::string direction, std::vector<QGraphicsRectItem*> moving_shape,  bool creating = false);

    /**
     * @brief makes corner shaped element
     * @brief LEFT, RIGHT or UP(means pyramid)
     * @param direction, which direction the corner is
     */
    void make_corner(std::string direction);

    /**
     * @brief makes steps shaped element
     * @brief LEFT, RIGHT or UP(means big square)
     * @param direction, which direction the step is
     */
    void make_steps(std::string direction);

    /**
     * @brief connects 2 shapes together
     * @param vector that contains shapes, to this shape will be added second shape
     * @param second vector that contains shapes, will be removed after connceting
     */
    void connect_shapes(std::vector<QGraphicsRectItem *>& first_shape, std::vector<QGraphicsRectItem *>& second_shape);


    // Methods for helping shape to move correctly and choosing shapes

    /**
     * @brief checks if some part of the shape hits bottom of the screen
     * @brief or hits other shape under it
     * @return true if hits, false if doesnt hit
     */
    bool is_hitting_bottom_or_other_shape();

    /**
     * @brief checks if some part of the shape goes out of screen
     * @return string that tells which direction shape can move
     */
    std::string allowed_to_move();

    /**
     * @brief chooses right shape, works with randomEng
     * @brief randomEngs chosen shape by its number comes from private chosen_shape_
     */
    void choose_shape();

    /**
     * @brief checks if rectangle isnt part of moving shape
     * @param rectangle currectly near rect that is observed
     * @return true if its part of the shape, false if its already landed shape
     */
    bool is_rect_from_same_shape(QGraphicsItem *object_rect);

    //rotation methods (hard to do, Its a little bit of a mess, sry)

    /**
     * @brief rotates 2 or 3 rectangles to correct positions so horizontal shape rotates
     * @param when param four_shape true, rotates HORIZONTAL shape
     * @return bool that changes what rotation shape is, is it horizontaly or vertically
     */
    bool rotate_horizontal(bool four_shape = false);

    /**
     * @brief rotates rectangle to correct positions so CORNER shape rotates correctly
     * @param when param reverse true, rotates to other way (helps with left and right corners)
     * @return bool that changes what rotation shape is, is it horizontaly or vertically
     * @return and changes between first_rotation_ true or false (corner shapes have 4 rotation)
     */
    bool rotate_one_piece(bool reverse = false);

    /**
     * @brief rotates rectangles to correct positions so STEP shape rotates correctly
     * @param when param reverse true, rotates to other way (helps with left and right corners)
     * @return bool that changes what rotation shape is, is it horizontaly or vertically
     * @return and changes between first_rotation_ true or false (corner shapes have 4 rotation)
     */
    bool rotate_steps(bool reverse = false);

    /**
     * @brief rotates rectangle to correct positions so PYRAMID shape rotates correctly
     * @return bool that changes what rotation shape is, is it horizontaly or vertically
     * @return and changes between first_rotation_ true or false (corner shapes have 4 rotation)
     */
    bool rotate_pyramide();

    /**
     * @brief stops timer and ends game if shape is top and it has block under it
     */
    void end_game();

    /**
     * @brief deletes all full, rows. Problem with valgrid!
     */
    int delete_full_rows();

    /**
     * @brief checks rotation to next cordinates is allowed
     */
    bool is_rotation_allowed(std::vector<std::vector<qreal>> cors);

    /**
     * @brief checks y_real_pos is added to y_coordinates
     * @param y_cordinates shapes y coordinates
     * @param y_pos from delete_full_rows methods
     * @return bool true if its already there
     */
    bool is_added(std::vector<qreal> y_cordinates, qreal y_real_pos);

    /**
     * @brief changes game difficulty setting (speed_)
     */
    void difficulty_check();
private slots:

    /**
     * @brief slot connected to timer timeout signal
     */
    void start_game();

    /**
     * @brief left button moves shape to left
     */
    void on_leftPushButton_clicked();

    /**
     * @brief right button moves shape to right
     */
    void on_rightPushButton_clicked();

    /**
     * @brief down button moves shape to down
     */
    void on_downPushButton_clicked();

    /**
     * @brief starts timer and timer is connected to dropping shapes
     */
    void on_startPushButton_clicked();

    /**
     * @brief resets game
     */
    void on_resetPushButton_clicked();

    /**
     * @brief rotates shape correctly depending on its shape
     */
    void on_rotatePushButton_clicked();
};

#endif // MAINWINDOW_HH
