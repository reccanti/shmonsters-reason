/**
 * This class is used to interact with the canvas
 * component using regular JavaScript and will be
 * wrapped by ReasonReact code 
 */
import React from "react";
import PropTypes from "prop-types";

export default class JsCanvas extends React.Component {

    static propTypes = {
        width: PropTypes.string.isRequired,
        height: PropTypes.string.isRequired,
        initialDataUrl: PropTypes.string,
        onChange: PropTypes.func
    }

    static defaultProps = {
        initialDataUrl: "",
        onChange() { },
    }

    constructor(props) {
        super(props);
        this.state.dataUrl = props.initialDataUrl;
    }

    state = {
        drawingCanvas: null,
        drawingContext: null,
        mouseCanvas: null,
        mouseContext: null,
        mouseDown: false,
        dataUrl: ""
    }


    createDrawingCanvas = element => {
        if (element) {
            const drawingCanvas = element;
            const drawingContext = element.getContext("2d");

            // draw the dataURL provided on the canvas
            const img = new Image();
            img.onload = () => {
                drawingContext.drawImage(img, 0, 0);
            }
            img.src = this.props.initialDataUrl;
            this.setState({
                drawingCanvas,
                drawingContext
            });
        }
    }

    createMouseCanvas = element => {
        if (element) {
            this.setState({
                mouseCanvas: element,
                mouseContext: element.getContext("2d")
            });
        }
    }

    handleMouseMove = event => {
        // create the hover state
        const canvasSize = this.state.mouseCanvas.getBoundingClientRect();
        const mouseX = Math.floor(((event.clientX - canvasSize.left) / canvasSize.width) * this.props.width);
        const mouseY = Math.floor(((event.clientY - canvasSize.top) / canvasSize.height) * this.props.height);
        this.state.mouseContext.clearRect(0, 0, this.props.width, this.props.height);
        this.state.mouseContext.fillStyle = "gray";
        this.state.mouseContext.fillRect(mouseX, mouseY, 1, 1);

        // draw to the canvas below
        if (this.state.mouseDown) {
            this.state.drawingContext.fillStyle = "white";
            this.state.drawingContext.fillRect(mouseX, mouseY, 1, 1);
        }
    }

    handleMouseDown = event => {
        this.setState({
            mouseDown: true
        });
    }

    handleMouseUp = event => {
        const dataUrl = this.state.drawingCanvas.toDataURL("image/png");
        this.setState({
            mouseDown: false,
            dataUrl
        });
        this.props.onChange(dataUrl);
    }

    render() {
        return (
            <div style={{ position: "relative" }}>
                {/* Mouse canvas */}
                <canvas
                    ref={this.createMouseCanvas}
                    style={{ width: "100%", height: "auto", imageRendering: "pixelated", position: "absolute" }}
                    width={this.props.width}
                    height={this.props.height}
                    onMouseMove={this.handleMouseMove}
                    onMouseDown={this.handleMouseDown}
                    onMouseUp={this.handleMouseUp}
                />
                {/* Image canvas */}
                <canvas
                    ref={this.createDrawingCanvas}
                    style={{ width: "100%", height: "auto", imageRendering: "pixelated" }}
                    width={this.props.width}
                    height={this.props.height}
                />
            </div>
        )
    }
}