/*
* ----------
* TIE-02201/TIE-02207 SPRING 2020
* ----------
*
* Tetris project
* Name: Lari Lantonen
* Student number: 283531
* UserID: lantonen
* E-Mail: lari.lantonen@tuni.fi
*
* Notes about the program and it's implementation:
* instuctions.txt has all information
*
* */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "iostream"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);
    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed. distr(randomEng)

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &MainWindow::start_game);
    connect(timer_, &QTimer::timeout, this, &MainWindow::end_game);

    ui->textBrowser->setStyleSheet("font: 20pt 'Times New Roman';");

    ui->leftPushButton->setDisabled(true);
    ui->rightPushButton->setDisabled(true);
    ui->rotatePushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);

    ui->easyRadioButton->toggle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsRectItem* MainWindow::make_small_square(int x,int y, QColor brush_color, QColor pen_color){
    QBrush brush(brush_color);
    QPen pen(pen_color);

    rectangle_ = scene_->addRect(4 * SQUARE_SIDE, -2 * SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE, pen, brush);
    if ( x != 0 ){
        for(int i = 0; i < x/SQUARE_SIDE; i++){

            rectangle_->moveBy(SQUARE_SIDE, 0);
        }

    }
    if( y != 0 ){
        for(int i = 0; i < y/SQUARE_SIDE; i++){

            rectangle_->moveBy(0, SQUARE_SIDE);
        }
    }
    return rectangle_;
}

std::vector<QGraphicsRectItem*> MainWindow::make_horizontal(int amount, QColor brush_color, int y){
    int xCor = 0;
    int yCor = y;
    std::vector<QGraphicsRectItem*> new_shape;
    QGraphicsRectItem* new_item;
    for(int i = 0; i < amount; i++){
        new_item = make_small_square(xCor, yCor, brush_color);
        xCor += SQUARE_SIDE;
        new_shape.push_back(new_item);
    }
    return new_shape;
}

void MainWindow::move_it(std::string direction, std::vector<QGraphicsRectItem*> moving_shape, bool creating){
    std::string access_to_move = "both";

    if(not creating){
       access_to_move = allowed_to_move();
    }

    //moving for move right button
    if(direction == RIGHT){
        if(access_to_move == RIGHT or access_to_move == "both"){
            for(auto rectangle : moving_shape){
                rectangle->moveBy(SQUARE_SIDE, 0);
            }
        }
    }

    //moving for move left button
    else if(direction == LEFT){
        if(access_to_move == LEFT or access_to_move == "both"){
            for(auto rectangle : moving_shape){
                rectangle->moveBy(-SQUARE_SIDE, 0);
            }
        }
    }

    // moving down
    if(direction == DOWN){
        for(auto rectangle : moving_shape){
            rectangle->moveBy(0, SQUARE_SIDE);
        }
    }


}

void MainWindow::make_corner(std::string direction){
    if(direction == LEFT){
        int xCor = 0;
        int yCor = 0;


        shape_ = make_horizontal(3, Qt::gray, SQUARE_SIDE);
        shape_.push_back(make_small_square(xCor, yCor, Qt::gray));

    }
    //right corner
    else if(direction == RIGHT){
        int xCor = 2*SQUARE_SIDE;
        int yCor = 0;


        shape_ = make_horizontal(3, Qt::red, SQUARE_SIDE);
        shape_.push_back(make_small_square(xCor, yCor, Qt::red));
    }
    // pyramid
    else if(direction == UP){
        int xCor = SQUARE_SIDE;
        int yCor = 0;


        shape_ = make_horizontal(3, Qt::darkMagenta, SQUARE_SIDE);
        shape_.push_back(make_small_square(xCor, yCor, Qt::darkMagenta));
    }
}

void MainWindow::make_steps(std::string direction){
    //left step
    if(direction == LEFT){

        std::vector<QGraphicsRectItem*> temp_shape;
        shape_ = make_horizontal(2, Qt::green, SQUARE_SIDE);
        move_it(RIGHT, shape_, true);
        temp_shape = make_horizontal(2, Qt::green, 0);
        connect_shapes(shape_, temp_shape);


    }
    //right step
    else if(direction == RIGHT){

        std::vector<QGraphicsRectItem*> temp_shape;
        temp_shape = make_horizontal(2, Qt::darkGreen, 0);
        shape_ = make_horizontal(2, Qt::darkGreen, SQUARE_SIDE);


        move_it(RIGHT, temp_shape, true);
        connect_shapes(shape_, temp_shape);
    }
    //big square
    else if(direction == UP){
        std::vector<QGraphicsRectItem*> temp_shape;
        shape_ = make_horizontal(2, Qt::magenta, 0);
        temp_shape = make_horizontal(2, Qt::magenta, SQUARE_SIDE);
        connect_shapes(shape_, temp_shape);
    }
}
//connects second shape to first shape
void MainWindow::connect_shapes(std::vector<QGraphicsRectItem*>& first_shape, std::vector<QGraphicsRectItem*>& second_shape){
    for(auto shape : second_shape){
        first_shape.push_back(shape);
    }
}

void MainWindow::start_game(){



    if(is_hitting_bottom_or_other_shape()){
        score_ += 20 * delete_full_rows();

        score_++;
        ui->scoreLcdNumber->display(score_);

        horizontal_up_ = false;
        first_rotation_ = true;

        chosen_shape_ = distr(randomEng);
        choose_shape();
    }
    else{
        move_it(DOWN, shape_);
    }
}

void MainWindow::on_leftPushButton_clicked()
{

    move_it(LEFT, shape_);
}

void MainWindow::on_rightPushButton_clicked()
{
    move_it(RIGHT, shape_);
}

void MainWindow::on_downPushButton_clicked()
{
    end_game();
    while(not is_hitting_bottom_or_other_shape()){
        move_it(DOWN, shape_);
    }

}

bool MainWindow::is_hitting_bottom_or_other_shape(){

    for(auto rect : shape_){

        QTransform transform;

        qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
        qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
        QGraphicsItem* under_my_rect = scene_->itemAt(QPointF(x_real_pos + 1, y_real_pos + SQUARE_SIDE + 1), transform);

        //hits to bottom
        if(y_real_pos >= BORDER_DOWN - SQUARE_SIDE){

            return true;
        }
        else if(!is_rect_from_same_shape(under_my_rect) and under_my_rect != nullptr){

            return true;
        }
    }
    return false;
}

bool MainWindow::is_rect_from_same_shape(QGraphicsItem* object_rect){
    for(auto rect : shape_){

        if(rect == object_rect){
            return true;
        }
    }
    return false;
}

std::string MainWindow::allowed_to_move(){
    QRectF board = scene_->sceneRect();
    std::string access_right = "yes";
    std::string access_left = "yes";

    for(auto rect : shape_){

        qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
        qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;

        QTransform transform;
        QGraphicsItem* left_to_my_rect = scene_->itemAt(QPointF(x_real_pos - SQUARE_SIDE + 1, y_real_pos + 1), transform);
        QGraphicsItem* right_to_my_rect = scene_->itemAt(QPointF(x_real_pos + SQUARE_SIDE + 1, y_real_pos + 1), transform);

        //is there shape blocking left
        if(!is_rect_from_same_shape(left_to_my_rect) and left_to_my_rect != nullptr){
            access_left = "prevented";
        }
        //blocking right
        else if(!is_rect_from_same_shape(right_to_my_rect) and right_to_my_rect != nullptr){
            access_right = "prevented";
        }


        //out of bounds right side so prevent moving RIGHT
        if(!board.contains(x_real_pos + SQUARE_SIDE, y_real_pos)){
            access_right = "prevented";
        }
        //out of bounds left side so prevent moving LEFT
        if(!board.contains(x_real_pos - 1, y_real_pos)){
            access_left = "prevented";
        }


    }
    if(access_left == "prevented" and access_right == "prevented"){
        return DOWN;
    }
    else if(access_left == "prevented"){
        return RIGHT;
    }
    else if(access_right == "prevented"){
        return LEFT;
    }
    else{
        return "both";
    }


}

void MainWindow::choose_shape(){
    if(chosen_shape_ == HORIZONTAL){
        shape_ = make_horizontal(4, Qt::cyan);
    }
    else if(chosen_shape_ == LEFT_CORNER){
        make_corner(LEFT);
    }
    else if(chosen_shape_ == RIGHT_CORNER){
        make_corner(RIGHT);
    }
    else if(chosen_shape_ == SQUARE){
        make_steps(UP);
    }
    else if(chosen_shape_ == STEP_UP_RIGHT){
        make_steps(RIGHT);
    }
    else if(chosen_shape_ == PYRAMID){
        make_corner(UP);
    }
    else if(chosen_shape_ == STEP_UP_LEFT){
        make_steps(LEFT);
    }

}

void MainWindow::on_startPushButton_clicked()
{
    chosen_shape_ = distr(randomEng);
    choose_shape();


    ui->startPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(false);
    ui->rightPushButton->setDisabled(false);
    ui->rotatePushButton->setDisabled(false);
    ui->downPushButton->setDisabled(false);
    ui->textBrowser->setPlainText("TETRIS");

    difficulty_check();
    timer_->start(speed_);
}

void MainWindow::on_resetPushButton_clicked()
{
    timer_->stop();
    ui->startPushButton->setDisabled(false);
    ui->leftPushButton->setDisabled(true);
    ui->rightPushButton->setDisabled(true);
    ui->rotatePushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);

    delete scene_;
    scene_ = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    chosen_shape_ = distr(randomEng);
    score_ = 0;
    ui->scoreLcdNumber->display(score_);

    horizontal_up_ = false;
    first_rotation_ = true;
}

void MainWindow::on_rotatePushButton_clicked(){
    std::vector<std::vector<qreal>> cordinates = {};
    //kumpikin suunta
    if(chosen_shape_ == HORIZONTAL){

        horizontal_up_ = rotate_horizontal(true);
        for(int index = 0; index < 4; index++ ){
            QGraphicsItem* rect = shape_[index];
            qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
            qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
            // rotates around second rectangle
            if(index != 1){
                cordinates.push_back({x_real_pos, y_real_pos});
            }

        }
        for(int i = 0 ; i < 3 ; i++){
            horizontal_up_ = rotate_horizontal(true);
        }
        if(is_rotation_allowed(cordinates)){
            horizontal_up_ = rotate_horizontal(true);
        }

    }
    //left over
    else if(chosen_shape_ == LEFT_CORNER){
        first_rotation_ = rotate_one_piece();
        horizontal_up_ = rotate_horizontal();
        for(int index = 0; index < 4; index++ ){
            QGraphicsItem* rect = shape_[index];
            qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
           qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
            // rotates around second rectangle
            if(index != 1){
                cordinates.push_back({x_real_pos, y_real_pos});
            }

        }
        for(int i = 0 ; i < 3 ; i++){
            first_rotation_ = rotate_one_piece();
            horizontal_up_ = rotate_horizontal();
        }
        if(is_rotation_allowed(cordinates)){
            first_rotation_ = rotate_one_piece();
            horizontal_up_ = rotate_horizontal();
        }


    }
    //right over
    else if(chosen_shape_ == RIGHT_CORNER){

        for(int i = 0 ; i < 3 ; i++){
            first_rotation_ = rotate_one_piece(true);
            horizontal_up_ = rotate_horizontal();
        }
        for(int index = 0; index < 4; index++ ){
            QGraphicsItem* rect = shape_[index];
            qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
           qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
            // rotates around second rectangle
            if(index != 1){
                cordinates.push_back({x_real_pos, y_real_pos});
            }

        }
        first_rotation_ = rotate_one_piece(true);
        horizontal_up_ = rotate_horizontal();

        if(is_rotation_allowed(cordinates)){
            for(int i = 0 ; i < 3 ; i++){
                first_rotation_ = rotate_one_piece(true);
                horizontal_up_ = rotate_horizontal();
            }
        }
    }
    else if(chosen_shape_ == SQUARE){
    }
    //from left over
    else if(chosen_shape_ == STEP_UP_RIGHT){

        first_rotation_ = rotate_steps();
        horizontal_up_ = rotate_horizontal(true);
        for(int index = 0; index < 4; index++ ){
            QGraphicsItem* rect = shape_[index];
            qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
            qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
            // rotates around second rectangle
            if(index != 1 and index != 0 and !first_rotation_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }
            else if(index != 1 and index != 2 and first_rotation_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }

        }
        for(int i = 0 ; i < 3 ; i++){
            first_rotation_ = rotate_steps();
            horizontal_up_ = rotate_horizontal(true);
        }
        if(is_rotation_allowed(cordinates)){
            first_rotation_ = rotate_steps();
            horizontal_up_ = rotate_horizontal(true);

        }
    }
    else if(chosen_shape_ == PYRAMID){


        first_rotation_ = rotate_pyramide();
        horizontal_up_ = rotate_horizontal();

        for(int index = 0; index < 4; index++ ){
            QGraphicsItem* rect = shape_[index];
            qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
            qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
            // only rectange needed to check is 3. so index 2
            if(index == 2 and first_rotation_ and horizontal_up_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }
            // only rectange needed to check is 1.
            else if(index == 0 and !first_rotation_ and !horizontal_up_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }
            // only rectange needed to check is 1 .
            else if(index == 0 and !first_rotation_ and horizontal_up_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }
            // only rectange needed to check is 3.
            else if(index == 2 and first_rotation_ and !horizontal_up_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }


        }
        for(int i = 0 ; i < 3 ; i++){
            first_rotation_ = rotate_pyramide();
            horizontal_up_ = rotate_horizontal();
        }
        if(is_rotation_allowed(cordinates)){
            first_rotation_ = rotate_pyramide();
            horizontal_up_ = rotate_horizontal();
        }



    }
    // from right
    else if(chosen_shape_ == STEP_UP_LEFT){
        first_rotation_ = rotate_steps();
        horizontal_up_ = rotate_horizontal(true);


        for(int index = 0; index < 4; index++ ){
            QGraphicsItem* rect = shape_[index];
            qreal x_real_pos = rect->x() + 4 * SQUARE_SIDE;
            qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
            // rotates around second rectangle
            if(index != 1 and index != 2 and !first_rotation_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }
            else if(index != 1 and index != 0 and first_rotation_){
                cordinates.push_back({x_real_pos, y_real_pos});
            }

        }
        for(int i = 0 ; i < 3 ; i++){
            first_rotation_ = rotate_steps();
            horizontal_up_ = rotate_horizontal(true);
        }

        if(is_rotation_allowed(cordinates)){
            first_rotation_ = rotate_steps();
            horizontal_up_ = rotate_horizontal(true);
        }

    }

}

bool MainWindow::rotate_horizontal(bool four_shape){

    if(horizontal_up_){
        //rotates vertical to horizontal
        shape_[0]->moveBy(-SQUARE_SIDE, SQUARE_SIDE);
        shape_[2]->moveBy(SQUARE_SIDE, -SQUARE_SIDE);
        if(four_shape){
            shape_[3]->moveBy(2 * SQUARE_SIDE, -2 * SQUARE_SIDE);
        }

        return false;
    }
    else{
        //rotates horizontal to vertical
        shape_[0]->moveBy(SQUARE_SIDE, -SQUARE_SIDE);
        shape_[2]->moveBy(-SQUARE_SIDE, SQUARE_SIDE);
        if(four_shape){
            shape_[3]->moveBy(-2 * SQUARE_SIDE, 2 * SQUARE_SIDE);
        }
        return true;
    }

}

bool MainWindow::rotate_one_piece(bool reverse){

    if (reverse){
        if(first_rotation_){
            first_rotation_ = false;
        }
        else{
            first_rotation_ = true;
        }
    }

    if(!horizontal_up_ and first_rotation_){
        //rotates horizontal to vertical and first rotation
        shape_[3]->moveBy(2 * SQUARE_SIDE, 0);
        }
    else if (horizontal_up_ and first_rotation_){
        //rotates vertical to horizontal and first rotation
        shape_[3]->moveBy(0, 2 * SQUARE_SIDE);
        return false;
    }
    else if(!horizontal_up_ and !first_rotation_){
        //rotates vertical to horizontal and second rotation
        shape_[3]->moveBy(-2 * SQUARE_SIDE, 0);
        return false;
    }

    else{
        //rotates horizontal to vertical and second rotation
        shape_[3]->moveBy(0, -2 * SQUARE_SIDE);
    }

    return true;

}

bool MainWindow::rotate_steps(bool reverse){

    if (reverse){
        if(first_rotation_){
            first_rotation_ = false;
        }
        else{
            first_rotation_ = true;
        }
    }


    if(!first_rotation_){
        shape_[2]->moveBy(-2*SQUARE_SIDE, 0);
        shape_[3]->moveBy(-2*SQUARE_SIDE, 0);
        return true;
    }
    else{
        shape_[2]->moveBy(2*SQUARE_SIDE, 0);
        shape_[3]->moveBy(2*SQUARE_SIDE, 0);
        return false;
    }


}

bool MainWindow::rotate_pyramide(){

    if(!horizontal_up_ and first_rotation_){
        //rotates horizontal to vertical and first rotation
        shape_[3]->moveBy(SQUARE_SIDE, SQUARE_SIDE);
        return true;
        }
    else if (horizontal_up_ and first_rotation_){
        //rotates vertical to horizontal and first rotation
        shape_[3]->moveBy(-SQUARE_SIDE, SQUARE_SIDE);
        return false;

    }
    else if(!horizontal_up_ and !first_rotation_){
        //rotates vertical to horizontal and second rotation
        shape_[3]->moveBy(-SQUARE_SIDE, -SQUARE_SIDE);
        return false;

    }
    else if (horizontal_up_ and !first_rotation_){
        //rotates horizontal to vertical and second rotation
        shape_[3]->moveBy(SQUARE_SIDE, -SQUARE_SIDE);
        return true;
    }
    return true;
}

void MainWindow::end_game(){
    for(auto rect : shape_){
        qreal y_real_pos = rect->y() - 2 * SQUARE_SIDE;
        if(y_real_pos == 0 and is_hitting_bottom_or_other_shape()){
            timer_->stop();
            ui->textBrowser->setPlainText("Game over! \n Score :" + QString::number(score_));
            ui->startPushButton->setDisabled(true);
        }
    }

}

int MainWindow::delete_full_rows(){
    QTransform transform;
    std::vector<qreal> y_cordinates = {};
    std::vector<qreal> full_y_vector = {};
    //finds all shapes y coordinate
    //jostain tässä aiheuttaa valgrid issues, apua?
    for(auto rect : shape_){
        if(not is_added(y_cordinates, rect->y() - 2 * SQUARE_SIDE)){
            y_cordinates.push_back(rect->y() - 2 * SQUARE_SIDE);
        }
    }

    std::vector<std::vector<QGraphicsItem*>> temp_vector = {};
    int counter = 0;
    for(auto y_pos : y_cordinates){
        bool full_row = true;
        std::vector<QGraphicsItem*> temp_row;

        for(int i = 1; i < BORDER_RIGHT; i += SQUARE_SIDE){
            QGraphicsItem* temp_item = scene_->itemAt(QPointF(i, y_pos + 1), transform);
            if( temp_item == nullptr){
                full_row = false;
                break;
            }
            else{
                temp_row.push_back(temp_item);
            }
        }
        if(full_row){

            qreal y = y_pos;
            full_y_vector.push_back(y);
            temp_vector.push_back(temp_row);
        }

    }

    //dropping items down

    for(auto full_y : full_y_vector){

        QList<QGraphicsItem*> scene_items = scene_->items();
        for(auto item : scene_items){
            if(item->y() - 2 * SQUARE_SIDE < full_y){
                item->moveBy(0, SQUARE_SIDE);
            }
        }
    }



    //deleting all items
    for(auto row : temp_vector){
        counter++;
        for(auto item : row){
            delete item;
        }
    }

    return counter;
}

bool MainWindow::is_added(std::vector<qreal> y_cordinates, qreal y_real_pos){
    for(auto qreal_pos : y_cordinates){
        if(y_real_pos == qreal_pos){
            return true;
        }
    }
    return false;
}

bool MainWindow::is_rotation_allowed(std::vector<std::vector<qreal>> cors) {
    QTransform transform;
    QRectF board = scene_->sceneRect();
    for(std::vector<qreal> one_cordinate : cors){
        //out of bounds
        if(!board.contains(one_cordinate[0], one_cordinate[1])){
            return false;
        }
        // contains block returns false
        else if(scene_->itemAt(QPointF(one_cordinate[0] + 1, one_cordinate[1] + 1), transform) != nullptr){
            return false;
        }
    }
    return true;
}

void MainWindow::difficulty_check(){
    if(ui->hardRadioButton->isChecked()){
        speed_ = 250;
    }
    else if(ui->mediumRadioButton->isChecked()){
        speed_ = 500;
    }
    else if(ui->easyRadioButton->isChecked()){
        speed_ = 750;
    }
}
