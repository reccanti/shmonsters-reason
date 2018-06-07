/**
 * This class is used to interact with the canvas
 * component using regular JavaScript and will be
 * wrapped by ReasonReact code 
 */
import React from "react";
import PropTypes from "prop-types";
import { request } from "https";

export default class JsCanvas extends React.Component {

    static propTypes = {
        width: PropTypes.string.isRequired,
        height: PropTypes.string.isRequired
    }

    state = {
        canvas: null,
        context: null
    }

    createCanvas = element => {
        this.setState({
            canvas: element,
            context: element.getContext("2d")
        });
    }

    handleMouseMove = event => {
        const canvasSize = this.state.canvas.getBoundingClientRect();
        const mouseX = Math.floor(((event.clientX - this.state.canvas.offsetLeft) / canvasSize.width) * this.props.width);
        const mouseY = Math.floor(((event.clientY - this.state.canvas.offsetTop) / canvasSize.height) * this.props.height);
        this.state.context.clearRect(0, 0, this.props.width, this.props.height);
        this.state.fillStyle = "gray";
        this.state.context.fillRect(mouseX, mouseY, 1, 1);
    }

    render() {
        return (
            <canvas
                ref={this.createCanvas}
                style={{width: "100%", height: "auto", imageRendering: "pixelated"}}
                width={this.props.width}
                height={this.props.height}
                onMouseMove={this.handleMouseMove}
            />
        )
    }
}